#include "app.hpp"

std::atomic<int> Worker::active = {0};

std::vector<pcpp::DpdkWorkerThread*> Worker::threads;

bool Worker::run(uint32_t coreId) {  //
    _coreId = coreId;
    active.fetch_add(1, std::memory_order_relaxed);
    return true;
}

bool Worker::terminate() {
    active.fetch_sub(1, std::memory_order_relaxed);
    return true;
}
