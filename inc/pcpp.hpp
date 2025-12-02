#pragma once

// #define MBUF_POOL_SZ (8192 - 1)
// #define MBUF_POOL_SZ (0x10000 - 1)
#define MBUF_POOL_SIZE (16 * 1024 - 1)

#define sendMac pcpp::MacAddress("e8:eb:d3:93:42:99")
#define recvMac pcpp::MacAddress("e8:eb:d3:93:42:91")
// "00:11:22:33:44:55")

#include <DpdkDevice.h>
#include <DpdkDeviceList.h>
#include <EthLayer.h>
#include <MacAddress.h>
#include <SystemUtils.h>
#include <sys/inotify.h>

#include <cassert>
#include <iostream>
#include <thread>

#include "types.hpp"

extern int main(int argc, char* argv[]);
extern void arg(int argc, char* argv);

class Watch {
    static std::vector<std::thread*> thread;
    static void watch(char* argv);

   public:
    static void init(int argc, char* argv[]);
};

class Dev {
    static pcpp::CoreMask coreMaskToUse;
    static pcpp::DpdkDevice* dev;

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

class Send : public Worker {
    pcpp::Packet packet;

   public:
    Send(pcpp::DpdkDevice* dev) : Worker(dev) {}
    bool run(uint32_t coreId);
};

class Stat : public Worker {
    pcpp::DpdkDevice::DpdkDeviceStats stats;

   public:
    Stat(pcpp::DpdkDevice* dev) : Worker(dev) {}
    bool run(uint32_t coreId);
};

class Group : public Worker {
    pcpp::DpdkDevice::DpdkDeviceStats stats;
    GROUP *g;

   public:
    Group(pcpp::DpdkDevice* dev, GROUP* g): Worker(dev),g(g) {}
    bool run(uint32_t coreId);
};
