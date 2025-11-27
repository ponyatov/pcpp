# rte_mempool
## Memory Pool Library
### [[DPDK]]

A memory pool is an allocator of a fixed-sized object

https://doc.dpdk.org/guides-24.11/prog_guide/mempool_lib.html

- Handle a pool of objects using [[ring]] to store
- bulk en-/dequeue
- per-CPU cache

used by: [[rte_mbuf]]
also: [[rte_ring]] [[rte_debug]]

In the [[DPDK]], it is identified by name and uses a [[rte_mempool|mempool]] handler to store free objects. The default mempool handler is [[ring]] based. It provides some other optional services such as 
- a per-core object cache and 
- an alignment helper to ensure that objects are padded 
	- to spread them equally on all [[DRAM]] or [[DDR3]] channels.
