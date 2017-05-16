/*
 * \brief  FatFS vfat library test
 * \author Emery Hemingway
 * \date   2016-05-22
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/heap.h>
#include <base/component.h>

/* Genode block backend */
#include <fatfs/block.h>

/* FatFS includes */
#include <fatfs/ff.h>

void Component::construct(Genode::Env &env)
{
	env.exec_static_constructors();

	Genode::Heap heap(env.ram(), env.rm());
	Fatfs::block_init(env, heap);

	FATFS fatfs;
	FRESULT fres = f_mount(&fatfs, (const TCHAR*)"0", 1);

	switch (fres) {
	case FR_OK:
		Genode::log("FR_OK"); break;
	case FR_INVALID_DRIVE:
		Genode::error("FR_INVALID_DRIVE"); break;
	case FR_DISK_ERR:
		Genode::error("FR_DISK_ERR"); break;
	case FR_NOT_READY:
		Genode::error("FR_NOT_READY"); break;
	case FR_NO_FILESYSTEM:
		Genode::error("FR_NO_FILESYSTEM"); break;
	default:
		Genode::error("unhandled error");
	}

	f_mount(nullptr, (const TCHAR*)"0", 0);
	env.parent().exit(fres != FR_OK);
}
