content: init.config machine.vbox

init.config:
	cp $(REP_DIR)/recipes/raw/vbox5-nova-serial/$@ $@

machine.vbox:
	cp $(REP_DIR)/recipes/raw/vbox5-nova-serial/$@ $@
