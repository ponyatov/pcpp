#pragma once

#include "net.hpp"

class Group : public Worker {
    pcpp::DpdkDevice::DpdkDeviceStats stats;
    GROUP* g;
    pcpp::Packet packet;

   public:
    Group(pcpp::DpdkDevice* dev, GROUP* g) : Worker(dev), g(g) {}
    bool run(uint32_t coreId);
};
