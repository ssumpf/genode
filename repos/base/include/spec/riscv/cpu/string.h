/*
 * \brief  CPU-specific memcpy
 * \author Sebastian Sumpf
 * \date   2015-06-01
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__RISCV__CPU__STRING_H_
#define _INCLUDE__RISCV__CPU__STRING_H_

namespace Genode {

	/**
	 * Copy memory block
	 *
	 * \param dst   destination memory block
	 * \param src   source memory block
	 * \param size  number of bytes to copy
	 *
	 * \return      number of bytes not copied
	 */
	inline size_t memcpy_cpu(void *dst, const void *src, size_t size)
	{

		unsigned char *d = (unsigned char *)dst, *s = (unsigned char *)src;

		size_t d_align = (size_t)dst & 0x7;
		size_t s_align = (size_t)src & 0x7;

		if (d_align != s_align)
		return size;

		/* copy to 8 byte alignment */
		for (; (size > 0) && (s_align > 0) && (s_align < 8);
		     s_align++, *d++ = *s++, size--);

		uint64_t *d8 = (uint64_t *)d;
		uint64_t *s8 = (uint64_t *)s;

		for (; size >= 8; size -= 8)
			*d8++ = *s8++;

		return size;
	}
}

#endif /* _INCLUDE__RISCV__CPU__STRING_H_ */
