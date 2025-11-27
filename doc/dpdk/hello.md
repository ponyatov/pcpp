# hello
## [[DPDK]]

https://doc.dpdk.org/guides/linux_gsg/linux_eal_parameters.html

The core of the application consists of two main parts: initializing the [[DPDK]] Environment Abstraction Layer ([[EAL]]) and launching a function on each [[lcore]]

[[EAL]] parameters:
- `lcores`
	```
	-l, --lcores <core list>
	```
- `main-lcore`
	- Core ID that is used as main (polling?)
	```
	--main-lcore <core ID>
	```

List of cores to run on


- `--lcores=1-3`
	- Run threads on physical CPUs 1, 2 and 3, with each thread having the same lcore id as the physical CPU id.

[[MDB]]