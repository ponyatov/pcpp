#pragma once

class Stat : public Worker {
    pcpp::DpdkDevice::DpdkDeviceStats stats;

   public:
    Stat(pcpp::DpdkDevice* dev) : Worker(dev) {}
    bool run(uint32_t coreId);
};
