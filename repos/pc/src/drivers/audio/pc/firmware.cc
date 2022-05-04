/*
 * \brief  Linux wireless stack
 * \author Josef Soentgen
 * \date   2018-06-29
 */

/*
 * Copyright (C) 2018-2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* Genode includes */
#include <base/log.h>
#include <rom_session/connection.h>

/* local includes */
#include <lx_kit/env.h>

using size_t = Genode::size_t;

struct Firmware_list
{
	char const *requested_name;
	size_t      size;
};


Firmware_list fw_list[] = {
	{ "sof-tgl.ri", 512768 },
	{ "sof-hda-generic-2ch.tplg", 47643 },
};


size_t fw_list_len = sizeof(fw_list) / sizeof(fw_list[0]);


/**********************
 ** linux/firmware.h **
 **********************/

extern "C" int lx_emul_request_firmware_nowait(const char *name, void **dest, size_t *result)
{
	if (!dest || !result)
		return -1;

	/* only try to load known firmware images */
	Firmware_list *fwl = 0;
	for (size_t i = 0; i < fw_list_len; i++) {
		if (Genode::strcmp(name, fw_list[i].requested_name) == 0) {
			fwl = &fw_list[i];
			break;
		}
	}

	if (!fwl) {
		Genode::error("firmware '", name, "' is not in the firmware white list");
		return -1;
	}

	char const *fw_name = fwl->requested_name;

	Genode::Rom_connection rom(Lx_kit::env().env, fw_name);
	Genode::Dataspace_capability ds_cap = rom.dataspace();

	if (!ds_cap.valid()) {
		Genode::error("could not get firmware ROM dataspace");
		return -1;
	}

	/* use allocator because fw is too big for slab */
	void *data = Lx_kit::env().heap.alloc(fwl->size);
	if (!data)
		return -1;

	void const *image = Lx_kit::env().env.rm().attach(ds_cap);
	Genode::memcpy(data, image, fwl->size);
	Lx_kit::env().env.rm().detach(image);

	*dest   = data;
	*result = fwl->size;

	return 0;
}


extern "C" void lx_emul_release_firmware(void const *data, size_t size)
{
	Lx_kit::env().heap.free(const_cast<void *>(data), size);
}
