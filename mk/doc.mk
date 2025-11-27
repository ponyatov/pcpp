.PHONY: doc
doc:
	rsync -r $(HOME)/metadoc/$(APP)/ doc/$(APP)/
	rsync -r $(HOME)/metadoc/legas/  doc/legas/

.PHONY: doxy
doxy: .doxygen doc/DoxygenLayout.xml doc/logo.png
	rm -rf doc/html ; doxygen $< 1>/dev/null
