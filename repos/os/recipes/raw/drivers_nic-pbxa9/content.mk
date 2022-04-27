content: drivers.config devices

devices:
	cp $(BASE_DIR)/board/pbxa9/$@ $@

drivers.config:
	cp $(REP_DIR)/recipes/raw/drivers_nic-pbxa9/$@ $@
