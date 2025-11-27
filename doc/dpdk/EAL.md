# EAL
## [[DPDK]] Environment Abstraction Layer
### [[rte_eal]]

https://doc.dpdk.org/guides-24.11/prog_guide/env_abstraction_layer.html

- responsible for gaining access to low-level resources such as hardware and memory space
- [[DPDK]] Loading and Launching (init)
- Core [[Affinity]]/Assignment Procedures
	- [[EAL]] provides mechanisms for assigning execution units to specific cores 
	- as well as creating execution instances

- [[DPDK]] loading and launching
- Support for multi-process and multi-thread execution types
- Core affinity/assignment procedures
- System memory allocation/de-allocation
- Atomic/lock operations
- Time reference
	- [[rte_timer]]
- PCI bus access
- Trace and debug functions
- CPU feature identification
- Interrupt handling
- Alarm operations
- Memory management ([[libc/malloc|malloc]])
	- [[rte_malloc]]
- logging


## [[multi-process socket]]