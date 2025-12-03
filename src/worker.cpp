#include "app.hpp"

std::atomic<int> Worker::active = {0};

std::vector<pcpp::DpdkWorkerThread*> Worker::threads;

Worker::Worker(pcpp::DpdkDevice* dev) : dev(dev), _stop(false) {
    coreMask = (coreMask << 1) | 0b10;
    Worker::threads.push_back(this);
}

bool Worker::run(uint32_t coreId) {
    _coreId = coreId;
    active.fetch_add(1, std::memory_order_relaxed);
    return true;
}

bool Worker::terminate() {
    active.fetch_sub(1, std::memory_order_relaxed);
    return true;
}

uint32_t Worker::coreMask = 0;
