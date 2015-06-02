
#ifndef _TRANSLATION_TABLE_H_
#define _TRANSLATION_TABLE_H_

#include <page_flags.h>
#include <page_slab.h>

namespace Genode
{
	class Translation_table;
}

class Genode::Translation_table
{
	public:

		static constexpr size_t MIN_PAGE_SIZE_LOG2 = 12;
		static constexpr size_t ALIGNM_LOG2        = 12;

		Translation_table()
		{
			PDBG("not impl");
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
		 * \param slab   second level page slab allocator
		 */
		void insert_translation(addr_t vo, addr_t pa, size_t size,
		                        Page_flags const & flags,  Page_slab * slab)
		{
			PDBG("not impl");
		}

		/**
		 * Remove translations that overlap with a given virtual region
		 *
		 * \param vo    region offset within the tables virtual region
		 * \param size  region size
		 * \param slab  second level page slab allocator
		 */
		void remove_translation(addr_t vo, size_t size, Page_slab * slab)
		{
			PDBG("not impl");
		}
};

#endif /* _TRANSLATION_TABLE_H_ */
