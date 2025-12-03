.PHONY: all run watch
all: bin/$(APP)
run: bin/$(APP)
	$^
watch: bin/$(APP)
# 	@$^ ; while [ true ]; do $^ ; done
	@$^ ; while [ $$? -eq 1 ]; do $^ ; done
