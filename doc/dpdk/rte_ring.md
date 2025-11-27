# rte_ring
## fixed-size lockless [[FIFO]]
### [[DPDK]]]

for storing object in a table

The [[ring]] structure provides a lockless multi-producer, multi-consumer [[FIFO]] API in a finite size table. It has some 

advantages over lockless queues; 
- easier to implement, 
- adapted to bulk operations and 
- faster.


