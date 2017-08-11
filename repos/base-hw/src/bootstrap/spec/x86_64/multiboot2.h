/*
 * \brief  Multiboot 2 handling
 * \author Alexander Boettcher
 * \date   2017-08-11
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__BOOTSTRAP__SPEC__X86_64__MULTIBOOT2_H_
#define _SRC__BOOTSTRAP__SPEC__X86_64__MULTIBOOT2_H_

/* base includes */
#include <util/mmio.h>

namespace Genode { class Multiboot2_info; }

class Genode::Multiboot2_info : Mmio
{
	private:

		struct Size : Register <0x0, 32> { };

		struct Tag : Genode::Mmio {
			enum { LOG2_SIZE = 3 };

			struct Type : Register <0x00, 32>
			{
				enum { END = 0, MEMORY = 6, ACPI_RSDP = 15 };
			};
			struct Size : Register <0x04, 32> { };

			Tag(addr_t addr) : Mmio(addr) { }
		};

		struct Acpi_rsdp : Mmio {
			struct Signature : Register <0x00, 64> { };
			struct Revision  : Register <0x0f,  8> { };
			struct Rsdt      : Register <0x10, 32> { };
			struct Xsdt      : Register <0x18, 64> { };

			Acpi_rsdp(addr_t addr) : Mmio(addr) { }

			bool valid() {
				/* XXX checksum verification missing */
				const char signature[] = "RSD PTR ";
				return read<Signature>() == *(uint64_t *)signature;
			}
		};

	public:

		enum { MAGIC = 0x36d76289UL };

		struct Memory : Genode::Mmio {
			enum { SIZE = 3 * 8 };

			struct Addr : Register <0x00, 64> { };
			struct Size : Register <0x08, 64> { };
			struct Type : Register <0x10, 32> { enum { MEMORY = 1 }; };

			Memory(addr_t mmap = 0) : Mmio(mmap) { }
		};

		Multiboot2_info(addr_t mbi) : Mmio(mbi) { }

        template <typename FUNC_MEM, typename FUNC_ACPI>
		void for_each_tag(FUNC_MEM mem_fn, FUNC_ACPI acpi_fn)
		{
			addr_t const size = read<Multiboot2_info::Size>();

			for (addr_t tag_addr = base() + (1UL << Tag::LOG2_SIZE);
			     tag_addr < base() + size;)
			{
				Tag tag(tag_addr);

				if (tag.read<Tag::Type>() == Tag::Type::END)
					return;

				if (tag.read<Tag::Type>() == Tag::Type::MEMORY) {
					addr_t mem_start = tag_addr + (1UL << Tag::LOG2_SIZE) + 8;
					addr_t const mem_end = tag_addr + tag.read<Tag::Size>();

					for (; mem_start < mem_end; mem_start += Memory::SIZE) {
						Memory mem(mem_start);
						mem_fn(mem);
					}
				}

				if (tag.read<Tag::Type>() == Tag::Type::ACPI_RSDP) {
					addr_t const rsdp_addr = tag_addr + (1UL << Tag::LOG2_SIZE);

					Acpi_rsdp rsdp(rsdp_addr);
					if (rsdp.valid())
						acpi_fn(rsdp.read<Acpi_rsdp::Revision>(),
						        rsdp.read<Acpi_rsdp::Rsdt>(),
						        rsdp.read<Acpi_rsdp::Xsdt>());
				}

				tag_addr += align_addr(tag.read<Tag::Size>(), Tag::LOG2_SIZE);
			}
		}
};

#endif /* _SRC__BOOTSTRAP__SPEC__X86_64__MULTIBOOT2_H_ */
