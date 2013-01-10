/*
 * \brief  Cpu specifi memcpy
 * \author Sebastian Sumpf
 * \date   2012-08-02
 */

/*
 * Copyright (C) 2012 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _INCLUDE__X86_32__CPU__STRING_H_
#define _INCLUDE__X86_32__CPU__STRING_H_

namespace Genode
{
	/**
	 * Copy memory block
	 *
	 * \param dst   destination memory block
	 * \param src   source memory block
	 * \param size  number of bytes to copy
	 *
	 * \return      Number of bytes not copied
	 */
	inline size_t memcpy_cpu(void *dst, const void *src, size_t size)
	{
		/* try to copy 32 byte chunks */
		size_t chunk = size / 32;
	
		if (!chunk)
			return size;
	
		asm volatile (
				"emms                             \n\t"
				"xor    %%ecx,%%ecx               \n\t"
				".align 16                        \n\t"
				"0:                               \n\t"
				"movq   (%%esi,%%ecx,8),%%mm0     \n\t"
				"movq   8(%%esi,%%ecx,8),%%mm1    \n\t"
				"movq   16(%%esi,%%ecx,8),%%mm2   \n\t"
				"movq   24(%%esi,%%ecx,8),%%mm3   \n\t"
				"movntq %%mm0,(%%edi,%%ecx,8)     \n\t"
				"movntq %%mm1,8(%%edi,%%ecx,8)    \n\t"
				"movntq %%mm2,16(%%edi,%%ecx,8)   \n\t"
				"movntq %%mm3,24(%%edi,%%ecx,8)   \n\t"
				"add    $4, %%ecx                 \n\t"
				"dec    %2                        \n\t"
				"jnz    0b                        \n\t"
				"sfence                           \n\t"
				"emms                             \n\t"
				:
				: "S" (src), "D" (dst), "r" (chunk)
				: "ecx", "memory"
		);
	
		return size % 32;
	}
}

#endif /* _INCLUDE__X86_32__CPU__STRING_H_ */
