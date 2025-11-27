# [[EAL]] multi-process socket

is a **communication mechanism** that allows multiple independent DPDK processes (both primary and secondary) to share a common memory region and synchronize their access to it.

"shared whiteboard" where different DPDK processes can:
- Announce their presence.
- Read and write configuration data.
- Share the memory maps for hugepages, device information, and ring/queue states.
- Coordinate access to hardware resources like NIC ports and queues.

As [[DPDK]] applications bypass the [[Linux/Linux|Linux]] kernel to interact directly with hardware, without this shared space, each DPDK process would have to map hardware resources independently, leading to conflicts and instability.

- how can separate processes safely and efficiently share access to the same NIC without the kernel's traditional mediation?
- [[multi-process socket]] solves this by providing a **standardized, userspace-based coordination plane**
	- [[rte_ring]] created in the primary process can be found and attached to by a secondary process
	- processes have a consistent view of the memory layout (hugepage mappings)
	- Only one process "owns" a specific RX/TX queue at a time, preventing data races.

## How It Works

The Socket File: 
```
EAL: Multi-process socket /run/user/1000/dpdk/rte/mp_socket
```
