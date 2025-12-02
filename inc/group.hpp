#pragma once

#include "net.hpp"

class Group : public Worker {
    pcpp::DpdkDevice::DpdkDeviceStats stats;
    GROUP* g;
    pcpp::Packet* packet;
    static const uint mbufArr_size = 0x100;
    pcpp::MBufRawPacket* mbufArr[mbufArr_size];
    pcpp::EthLayer* eth_layer;
    pcpp::IPv4Layer* ipv4_layer;
    pcpp::PayloadLayer* payload;

    /// @name fragmentation
    /// @{
    uint16_t ipId;  ///< transaction id
    /// @}

    uint sends;  ///< sends counter

    // uint frame;  ///< current frame counter
    /// packet frame buffer with optional UDP header
    struct __attribute__((packed)) FRAME {
        uint16_t src;
        uint16_t dst;
        uint16_t length = 0;
        uint16_t crc = 0;
        uint8_t data[Dev::MTU];
    } frame;

   public:
    Group(pcpp::DpdkDevice* dev, GROUP* g) : Worker(dev), g(g) {}
    bool run(uint32_t coreId);
};
