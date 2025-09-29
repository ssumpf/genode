content: hrd.tar

hrd.tar:
	rm -rf bin
	mkdir -p bin
	sed "1s/usr.//" $(GENODE_DIR)/tool/hrd > bin/hrd
	chmod 755 bin/hrd
	tar cf $@ --mtime='2025-09-29 00:00Z' bin
	rm -rf bin
