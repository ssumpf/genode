#pragma once

struct genode_mode {
	unsigned width;
	unsigned height;
	unsigned hz;
	unsigned brightness;
	unsigned enabled;
	unsigned preferred;
	unsigned id;
	char name[32];
};

void lx_emul_i915_report(void * lx_data, void * genode_xml);
void lx_emul_i915_hotplug_connector(void * lx_data);
void lx_emul_i915_report_connector(void * lx_data, void * genode_xml,
                                   char const *name, char connected,
                                   unsigned brightness);
void lx_emul_i915_iterate_modes(void *lx_data, void * genode_data);
void lx_emul_i915_report_modes(void * genode_xml, struct genode_mode *);
void lx_emul_i915_connector_config(char * name, struct genode_mode *);
