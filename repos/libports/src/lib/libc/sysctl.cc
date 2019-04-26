/*
 * \brief  Sysctl facade
 * \author Emery Hemingway
 * \date   2016-04-27
 */

/*
 * Copyright (C) 2016-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <util/string.h>
#include <base/env.h>

/* Genode-specific libc interfaces */
#include <libc-plugin/plugin.h>
#include <libc-plugin/fd_alloc.h>

/* Libc includes */
#include <sys/sysctl.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "libc_errno.h"
#include "libc_init.h"


enum { PAGESIZE = 4096 };


static Genode::Env *_global_env;


void Libc::sysctl_init(Genode::Env &env)
{
	_global_env = &env;
}


extern "C" long sysconf(int name)
{
	switch (name) {
	case _SC_CHILD_MAX:        return CHILD_MAX;
	case _SC_OPEN_MAX:         return getdtablesize();
	case _SC_NPROCESSORS_CONF: return 1;
	case _SC_NPROCESSORS_ONLN: return 1;
	case _SC_PAGESIZE:         return PAGESIZE;

	case _SC_PHYS_PAGES:
		return _global_env->pd().ram_quota().value / PAGESIZE;
	default:
		Genode::warning(__func__, "(", name, ") not implemented");
		return Libc::Errno(EINVAL);
	}
}


/* non-standard FreeBSD function not supported */
extern "C" int sysctlbyname(const char *name, void *, size_t *, const void *, size_t)
{
	Genode::warning(__func__, "(", name, ",...) not implemented");
	return Libc::Errno(ENOENT);
}
