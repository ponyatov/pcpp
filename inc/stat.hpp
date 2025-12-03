#pragma once

class Stat : public Worker {
    pcpp::DpdkDevice::DpdkDeviceStats stats;

   public:
    static Stat* single;
    Stat(pcpp::DpdkDevice* dev) : Worker(dev) {}
    bool run(uint32_t coreId);
};
