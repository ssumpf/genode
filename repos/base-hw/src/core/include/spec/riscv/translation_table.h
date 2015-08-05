/**
 * \brief  RISCV Sv39 page table format
 * \author Sebastian Sumpf
 * \date   2015-08-04
 */


#ifndef _TRANSLATION_TABLE_H_
#define _TRANSLATION_TABLE_H_

#include <util/register.h>

#include <page_flags.h>
#include <translation_table_allocator.h>

namespace Genode
{
	enum {
		SIZE_LOG2_4K   = 12,
		SIZE_LOG2_2M   = 21,
		SIZE_LOG2_1G   = 30,
		SIZE_LOG2_512G = 39,
	};

	struct None { };

	template <typename ENTRY, unsigned BLOCK_SIZE_LOG2, unsigned SIZE_LOG2>
	class Level_x_translation_table;

	using Level_3_translation_table =
		Level_x_translation_table<None, SIZE_LOG2_4K, SIZE_LOG2_2M>;

	using Level_2_translation_table =
		Level_x_translation_table<Level_3_translation_table, SIZE_LOG2_2M, SIZE_LOG2_1G>;

	using Level_1_translation_table =
		Level_x_translation_table<Level_2_translation_table, SIZE_LOG2_1G, SIZE_LOG2_512G>;
}


template <typename ENTRY, unsigned BLOCK_SIZE_LOG2, unsigned SIZE_LOG2>
class Genode::Level_x_translation_table
{
	private:

		bool _aligned(addr_t const a, size_t const alignm_log2) {
			return a == ((a >> alignm_log2) << alignm_log2); }

	public:

		static constexpr size_t MIN_PAGE_SIZE_LOG2 = SIZE_LOG2_4K;
		static constexpr size_t ALIGNM_LOG2        = SIZE_LOG2_4K;
		static constexpr size_t MAX_ENTRIES        = 1 << (SIZE_LOG2 - BLOCK_SIZE_LOG2);
		static constexpr size_t BLOCK_SIZE         = 1 << BLOCK_SIZE_LOG2;
		static constexpr size_t BLOCK_MASK         = ~(BLOCK_SIZE - 1);

		class Misaligned { };
		class Invalid_range { };
		class Double_insertion { };

		struct Descriptor : Register<64>
		{
			enum Descriptor_type { INVALID, TABLE, BLOCK };
			struct V    : Bitfield<0, 1>     { }; /* present */
			struct Type : Bitfield<1, 4>          /* type and access rights */
			{
				enum {
					POINTER        = 0,
					POINTER_GLOBAL = 1,
					USER           = 4, /* R + 0, RW + 1, RX + 2, RWX + 3 */
					KERNEL         = 8,
					GLOBAL         = 12,
				};
			};

			template <access_t BASE> 
			static access_t rwx(Page_flags const &f)
			{
				if (f.writeable && f.executable)
					return BASE + 3;
				else if (f.writeable)
					return BASE + 1;
				else if (f.executable)
					return BASE + 2;
				else
					return BASE;
			}

			static access_t permission_bits(Page_flags const &f)
			{
				if (f.global)
					return rwx<Type::GLOBAL>(f);

				if (f.privileged)
					return rwx<Type::KERNEL>(f);

				return rwx<Type::USER>(f);
			}

			static Descriptor_type type(access_t const v)
			{
				if (!V::get(v)) return INVALID;
				if (Type::get(v) == Type::POINTER || Type::get(v) == Type::POINTER_GLOBAL)
					return TABLE;

				return BLOCK;
			}

			static bool valid(access_t const v) {
				return V::get(v); }
		};

		struct Table_descriptor : Descriptor
		{
			struct Next_table : Descriptor::template Bitfield<10, 38> { };

			static typename Descriptor::access_t create(void * const pa)
			{
				typename Descriptor::access_t oa = (addr_t)pa;
				return Next_table::masked(oa)
				| Descriptor::Type::bits(Descriptor::Type::POINTER)
				| Descriptor::V::bits(1);
			}
		};

		struct Block_descriptor : Descriptor
		{
			struct Output_address : Descriptor::template Bitfield<10, 38> { };
			static typename Descriptor::access_t create(Page_flags const &f,
			                                            addr_t const pa)
			{
				typename Descriptor::access_t oa = (addr_t)pa;
				return Output_address::masked(oa)
					| Descriptor::Type::bits(Descriptor::permission_bits(f))
					| Descriptor::V::bits(1);
			}
		};

	protected:

		typename Descriptor::access_t _entries[MAX_ENTRIES];

		template <typename FUNC>
		void _range_op(addr_t vo, addr_t pa, size_t size, FUNC &&func)
		{
			for (size_t i = vo >> BLOCK_SIZE_LOG2; size > 0;
			     i = vo >> BLOCK_SIZE_LOG2) {
				addr_t end = (vo + BLOCK_SIZE) & BLOCK_MASK;
				size_t sz  = min(size, end-vo);

				func(vo, pa, sz, _entries[i]);

				/* check whether we wrap */
				if (end < vo) return;

				size = size - sz;
				vo  += sz;
				pa  += sz;
			}
		}

		template <typename E>
		struct Insert_func
		{
			Page_flags const    & flags;
			Translation_table_allocator * alloc;

			Insert_func(Page_flags const & flags,
			            Translation_table_allocator * alloc)
			: flags(flags), alloc(alloc) { }

			void operator () (addr_t const          vo,
			                  addr_t const          pa,
			                  size_t const          size,
			                  typename Descriptor::access_t &desc)
			{
				/* can we insert a whole block? */
				if (!((vo & ~BLOCK_MASK) || (pa & ~BLOCK_MASK) || size < BLOCK_SIZE)) {
					typename Descriptor::access_t blk_desc =
						Block_descriptor::create(flags, pa);

					if (Descriptor::valid(desc) && desc != blk_desc)
						throw Double_insertion();

					desc = blk_desc;
					return;
				}

				/* we need to use a next level table */
				ENTRY *table;
				switch (Descriptor::type(desc)) {

				case Descriptor::INVALID: /* no entry */
					{
						if (!alloc) throw Allocator::Out_of_memory();

						/* create and link next level table */
						table = new (alloc) ENTRY();
						ENTRY * phys_addr = (ENTRY*) alloc->phys_addr(table);
						desc = Table_descriptor::create(phys_addr ?
						                                phys_addr : table);
					}

				case Descriptor::TABLE: /* table already available */
					{
						/* use allocator to retrieve virt address of table */
						ENTRY * phys_addr = (ENTRY*)
							Table_descriptor::Next_table::masked(desc);
						table = (ENTRY*) alloc->virt_addr(phys_addr);
						table = table ? table : (ENTRY*)phys_addr;
						break;
					}

				case Descriptor::BLOCK: /* there is already a block */
					{
						throw Double_insertion();
					}
				};

				/* insert translation */
				table->insert_translation(vo - (vo & BLOCK_MASK),
				                          pa, size, flags, alloc);
			}
		};

		template <typename E>
		struct Remove_func
		{
			Translation_table_allocator * alloc;

			Remove_func(Translation_table_allocator * alloc) : alloc(alloc) { }

			void operator () (addr_t const                   vo,
			                  addr_t const                   pa,
			                  size_t const                   size,
			                  typename Descriptor::access_t &desc)
			{
				switch (Descriptor::type(desc)) {
				case Descriptor::TABLE:
					{
						/* use allocator to retrieve virt address of table */
						ENTRY * phys_addr = (ENTRY*)
							Table_descriptor::Next_table::masked(desc);
						ENTRY * table = (ENTRY*) alloc->virt_addr(phys_addr);
						table = table ? table : (ENTRY*)phys_addr;
						table->remove_translation(vo - (vo & BLOCK_MASK),
						                          size, alloc);
						if (!table->empty())
							break;
						destroy(alloc, table);
					}
				case Descriptor::BLOCK:
				case Descriptor::INVALID:
					desc = 0;
				}
			}
		};

	public:

		Level_x_translation_table()
		{
			if (!_aligned((addr_t)this, ALIGNM_LOG2))
				throw Misaligned();

			memset(&_entries, 0, sizeof(_entries));
		}

		bool empty()
		{
			for (unsigned i = 0; i < MAX_ENTRIES; i++)
				if (Descriptor::valid(_entries[i]))
					return false;
			return true;
		}

		/**
		 * Insert translations into this table
		 *
		 * \param vo     offset of the virtual region represented
		 *               by the translation within the virtual
		 *               region represented by this table
		 * \param pa     base of the physical backing store
		 * \param size   size of the translated region
		 * \param flags  mapping flags
		 * \param alloc  level allocator
		 */
		void insert_translation(addr_t vo, addr_t pa, size_t size,
		                        Page_flags const & flags,
		                        Translation_table_allocator * alloc )
		{
			PDBG("called");
			_range_op(vo, pa, size, Insert_func<ENTRY>(flags, alloc));
		}

		/**
		 * Remove translations that overlap with a given virtual region
		 *
		 * \param vo    region offset within the tables virtual region
		 * \param size  region size
		 * \param alloc level allocator
		 */
		void remove_translation(addr_t vo, size_t size,
		                        Translation_table_allocator * alloc)
		{
			PDBG("calledl");
			_range_op(vo, 0, size, Remove_func<ENTRY>(alloc));
		}
}  __attribute__((aligned(1 << ALIGNM_LOG2)));


namespace Genode {

	/**
	 * Insert/Remove functor specialization for level 3
	 */
	template <> template <>
	struct Level_3_translation_table::Insert_func<None>
	{
		Page_flags const            & flags;
		Translation_table_allocator * alloc;

		Insert_func(Page_flags const & flags,
		            Translation_table_allocator * alloc)
		: flags(flags), alloc(alloc) { }

			void operator () (addr_t const          vo,
			                  addr_t const          pa,
			                  size_t const          size,
			                  Descriptor::access_t &desc)
			{
				if ((vo & ~BLOCK_MASK) || (pa & ~BLOCK_MASK) ||
				    size < BLOCK_SIZE)
					throw Invalid_range();

				Descriptor::access_t blk_desc =
					Block_descriptor::create(flags, pa);

				if (Descriptor::valid(desc) && desc != blk_desc)
					throw Double_insertion();

				desc = blk_desc;
			}
	};

	template <> template <>
	struct Level_3_translation_table::Remove_func<None>
	{
		Remove_func(Translation_table_allocator * /* alloc */) { }

		void operator () (addr_t const          vo,
		                  addr_t const          pa,
		                  size_t const          size,
		                  Descriptor::access_t &desc) {
			desc = 0; }
	};

	class Translation_table : public Level_1_translation_table { };

} /* namespace Genode */

#endif /* _TRANSLATION_TABLE_H_ */
