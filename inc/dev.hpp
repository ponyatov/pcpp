#pragma once

#include <DpdkDevice.h>
#include <DpdkDeviceList.h>
#include <EthLayer.h>
#include <MacAddress.h>
#include <PacketUtils.h>
#include <PayloadLayer.h>
#include <SystemUtils.h>

#define sendMac pcpp::MacAddress("e8:eb:d3:93:42:99")
#define recvMac pcpp::MacAddress("e8:eb:d3:93:42:91")
// "00:11:22:33:44:55")

/// *More Fragments*: fragmentation flag mask
#define MF_flag 0b00100000

// #define DEBSEND

class Dev {
    static pcpp::CoreMask coreMaskToUse;
    static pcpp::DpdkDevice* dev;
    static const uint MBufPoolSize = (16 * 1024 - 1);

   public:
    static void sigint(void*);  ///< SIGINT callback
    static uint16_t MTU;
    static const uint16_t MTU_MAX = 1500;
    static void init(int argc, char* argv[]);
    static void stop();
};
