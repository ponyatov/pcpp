#pragma once

#include <DpdkDevice.h>
#include <DpdkDeviceList.h>
#include <EthLayer.h>
#include <MacAddress.h>
#include <SystemUtils.h>

#define sendMac pcpp::MacAddress("e8:eb:d3:93:42:99")
#define recvMac pcpp::MacAddress("e8:eb:d3:93:42:91")
// "00:11:22:33:44:55")

class Dev {
    static pcpp::CoreMask coreMaskToUse;
    static pcpp::DpdkDevice* dev;
    static const uint MTU = 1400;
    static const uint MBufPoolSize = (16 * 1024 - 1);

   public:
    static void init(int argc, char* argv[]);
    static std::vector<pcpp::DpdkWorkerThread*> workers;
    static bool _stop;
    static void stop();
    static void onApplicationInterrupted(void*);
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
