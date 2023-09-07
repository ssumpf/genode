#ifndef _SHADOW__LINUX__UTSNAME_H_
#define _SHADOW__LINUX__UTSNAME_H_

#include <uapi/linux/utsname.h>

extern struct new_utsname init_uts_ns;

static inline struct new_utsname *init_utsname(void)
{
	return &init_uts_ns;
}


static inline struct new_utsname *utsname(void)
{
	return init_utsname();
}

#endif /* _SHADOW__LINUX__UTSNAME_H_ */
