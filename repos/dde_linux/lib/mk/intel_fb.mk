#
# intel framebuffer driver as shared library without startup code
#
SHARED_LIB = yes
LIBS       = intel_fb_drv
LD_OPT    += --version-script=$(REP_DIR)/src/lib/framebuffer/intel/symbol.map
