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

class Dev {
    static pcpp::CoreMask coreMaskToUse;
    static pcpp::DpdkDevice* dev;
    static const uint MBufPoolSize = (16 * 1024 - 1);
    static std::vector<pcpp::DpdkWorkerThread*> workers;
    static bool _stop;
    static void signal();  ///< register @ref sigint

   public:
    static void sigint(void*);  ///< SIGINT callback
    static const uint MTU = 1400;
    static void init(int argc, char* argv[]);
};

class Worker : public pcpp::DpdkWorkerThread {
   protected:
    pcpp::DpdkDevice* dev;
    uint32_t _coreId;
    bool _stop;

   public:
    Worker(pcpp::DpdkDevice* dev) : dev(dev) { _stop = false; }
    void stop() { _stop = true; }
    uint32_t getCoreId() const { return dev->getCurrentCoreId(); }
};
