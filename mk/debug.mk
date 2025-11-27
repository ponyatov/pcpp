.PHONY: valg
valg: bin/$(BINFILE) $(S)
	valgrind $^ 2> tmp/$(APP).valgrind

# # Специальные настройки для работы с hugepages
# valgrind --trace-children=yes \
#          --track-origins=yes \
#          --leak-check=full \
#          --show-reachable=yes \
#          ./dpdk_app

# # Для hugepages требуется дополнительная настройка:
# valgrind --soname-synonyms=somalloc=nouserintercepts \
#          ./dpdk_app
