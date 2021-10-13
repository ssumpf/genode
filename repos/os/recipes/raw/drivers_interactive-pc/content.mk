content: drivers.config fb_drv.config event_filter.config en_us.chargen special.chargen gpu_drv.config

drivers.config fb_drv.config event_filter.config:
	cp $(REP_DIR)/recipes/raw/drivers_interactive-pc/$@ $@

gpu_drv.config:
	cp $(REP_DIR)/src/drivers/gpu/intel/$@ $@

en_us.chargen special.chargen:
	cp $(REP_DIR)/src/server/event_filter/$@ $@
