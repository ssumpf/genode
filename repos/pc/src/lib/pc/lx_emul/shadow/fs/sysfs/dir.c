/*
 * \brief  Dummy definitions of Linux Kernel sysfs functions
 * \author Josef Soentgen
 * \date   2022-04-05
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/sysfs.h>


int sysfs_create_dir_ns(struct kobject * kobj,const void * ns)
{
	lx_emul_trace(__func__);
	return 0;
}


void sysfs_remove_dir(struct kobject * kobj)
{
	lx_emul_trace(__func__);
}
