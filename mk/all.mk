PCI=0000:01:00.0

.PHONY: all run watch
all: bin/$(APP)
run: bin/$(APP)
	$^ -a $(PCI)
watch: bin/$(APP)
# 	@$^ ; while [ true ]; do $^ ; done
	@$^ ; while [ $$? -eq 1 ]; do $^ -a $(PCI) ; done
