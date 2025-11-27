# rte_mbuf
## packet buffers 
### [[DPDK]]

https://doc.dpdk.org/guides-24.11/prog_guide/mbuf_lib.html

The Packet ([[rte_mbuf]]) library provides the ability to allocate and free buffers (mbufs) that may be used by the [[DPDK]] application to store message buffers. The message buffers are stored in a [[rte_mempool|mempool]], using the Memory Pool Library.

A [[rte_mbuf]] struct generally carries network packet buffers, but it can actually be any data (control data, events, …). The rte_mbuf header structure is kept as small as possible and currently 
- uses just two cache lines, with the 
- most frequently used fields being 
	- on the first of the 
	- two cache lines.

