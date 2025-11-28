#include "app.hpp"

#ifndef DPDK_FOUND
#error DPDK required
#endif

void Net::init(int argc, char *argv[]) {  //
    std::cout << "\nrte:" << rte_eal_init(argc, argv) << '\n';
}
