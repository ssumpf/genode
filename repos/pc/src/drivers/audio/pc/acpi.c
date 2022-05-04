/*
 * \brief  Retrieve compiled in NHLT ACPI table
 *         (This needs to be obtained dynamically from ACPI)
 * \author Sebastian Sumpf
 * \date   2022-05-31
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/acpi.h>

#define ACPI_NHLT_DATA _binary_nhlt_fuji5c_dat_start

extern unsigned char ACPI_NHLT_DATA[];
static unsigned char *acpi_nhlt[] = { ACPI_NHLT_DATA };

acpi_status
acpi_get_table(char *signature,
               u32 instance, struct acpi_table_header ** out_table)
{
	if (strncmp(signature, ACPI_SIG_NHLT, 4) == 0) {
		*out_table = (struct acpi_table_header *)*acpi_nhlt;
		printk("%s: ACPI table '%s' found\n", __func__, signature);
		return AE_OK;
	}

	printk("%s: ACPI table '%s' not found\n",  __func__, signature);
	return AE_NOT_FOUND;
}


