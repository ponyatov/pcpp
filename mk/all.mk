.PHONY: all run watch
all: bin/$(BINFILE) $(S)
run: bin/$(BINFILE) $(S)
	$^
watch: bin/$(BINFILE) $(S)
# 	@ $^ ; echo _$$?_ ; while [ $$? -eq 1 ]; do $^ ; done
	@while [ true ]; do $^ ; echo _$$?_ ; sleep 1 ; done
