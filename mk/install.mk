.PHONY : install update ref gz
install: $(WS)_install doc ref gz
	$(MAKE) update
update : $(WS)_update
ref    : $(RF)
gz     : $(GZ)

Debian_install:
Debian_update: apt.Debian
	sudo apt update
	sudo apt install -uy `cat $<` $(APT)

Ubuntu_install:
Ubuntu_update: apt.Ubuntu
	sudo apt update
	sudo apt install -uy `cat $<` $(APT)
