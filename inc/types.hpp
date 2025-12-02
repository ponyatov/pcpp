#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "IPv4Layer.h"
#include "UdpLayer.h"

/// @brief UDP port configuration (send/recv)
struct UDP {
    pcpp::IPv4Address ip;  ///< IPV4
    uint16_t port;         ///< UDP port
};

/// @brief single @ref sensor configuration
struct SENSOR {
    std::string name;      ///<
    UDP src;               ///< @ref UDP for sender
    UDP dst;               ///< @ref UDP for receiver
    uint32_t sn;           ///< serial number
    std::string dataPath;  ///< file path for precomputed data

    /// @name precompiled data
    /// @{
    uint8_t* start;   ///<
    uint8_t* end;     ///<
    uint size;        ///< whole file size, bytes
    uint packetSize;  ///< single packet size, bytes
    uint packets;     ///< number of packets/data file
    uint16_t freq;    ///< poll frequency
    /// @}
};

/// @brief @ref SENSOR s group (single send with grouped packets)
struct GROUP {
    std::string name;              ///<
    uint duration;                 ///<
    bool loop;                     ///< repeat sending
    uint freq;                     ///<
    uint packetSize;               ///< UDP payload size, bytes
    std::vector<SENSOR*> sensors;  ///<
};

/// @brief statically-compiled configuration
struct CONFIG {
    uint baseCPUIndex;             ///< `=0` starting CPU core for DPDK
    std::vector<GROUP*> groups;    ///< sender groups
    std::vector<SENSOR*> sensors;  ///< list of all sensors in a system
};

extern CONFIG config;
