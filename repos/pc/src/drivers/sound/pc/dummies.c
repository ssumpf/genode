#include <lx_emul.h>

#include <linux/acpi.h>
acpi_status
acpi_get_table(char *signature,
               u32 instance, struct acpi_table_header ** out_table)
{
	lx_emul_trace_and_stop(__func__);
	return AE_NOT_FOUND;
}


void acpi_put_table(struct acpi_table_header *table)
{
	lx_emul_trace_and_stop(__func__);
}

