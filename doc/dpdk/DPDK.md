# DPDK
## Data Plane Development Kit

[[erl/edpdk]]

## book

https://doc.dpdk.org/guides-24.11/prog_guide/overview.html

The main goal of the DPDK is to provide a simple, complete framework for fast packet processing in data plane applications.

The [[DPDK]] framework creates a set of libraries for specific environments through the creation of an Environment Abstraction Layer ([[EAL]]), which may be specific to a mode of the Intel® architecture (32-bit or 64-bit), [[Linux/Linux|Linux]]* user space compilers or a specific platform. Other libraries, outside of EAL, including the Hash, Longest Prefix Match ([[net/LPM|LPM]]) and [[ring]]s libraries are also provided.

- **The DPDK model does not support a scheduler**
	- So [[QoS]]-like or timed traffic generator mechanics you must write yourself
- all devices are accessed **by polling**
	- The primary reason for not using interrupts is the performance overhead imposed by interrupt processing.

## 

These environments are created through the use of [[meson]] files and configuration files. Once the EAL library is created, the user may link with the library to create their own applications.  Sample applications are provided to help show the user how to use various features of the DPDK.

- passing packets or messages between cores via the rings
	- [[rte_mempool]]

## [[Linux/kernel|kernel]] [[bypass]]
## [[PcapPlusPlus]]

## [[EAL]]
## [[net/LPM|LPM]]
## [[IOVA]]

## [[Архитектура DPDK]]
## [[Захват и анализ трафика]]
## [[Генерация UDP-трафика]]
