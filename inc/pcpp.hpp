#pragma once

// #define MBUF_POOL_SZ (8192 - 1)
// #define MBUF_POOL_SZ (0x10000 - 1)
#define MBUF_POOL_SIZE (16 * 1024 - 1)

#include <DpdkDevice.h>
#include <DpdkDeviceList.h>
#include <SystemUtils.h>

#include <cassert>
#include <iostream>
#include <thread>

extern int main(int argc, char* argv[]);
extern void arg(int argc, char* argv);

class Dev {
    static pcpp::CoreMask coreMaskToUse;
    static pcpp::DpdkDevice* dev;

   public:
    static void init(int argc, char* argv[]);
    static std::vector<pcpp::DpdkWorkerThread*> workers;
    static bool _stop;
    static void on_close();
    static void onApplicationInterrupted(void*);
};

class Send : public pcpp::DpdkWorkerThread {
    pcpp::DpdkDevice* dev;
    bool stop;

    pcpp::Packet packet;

   public:
    Send(pcpp::DpdkDevice* dev) : dev(dev) {}
};

class Stat : public pcpp::DpdkWorkerThread {
    pcpp::DpdkDevice* dev;
    bool _stop;
    uint32_t _coreId;
    pcpp::DpdkDevice::DpdkDeviceStats stats;

   public:
    Stat(pcpp::DpdkDevice* dev) : dev(dev) { _stop = false; }
    void stop() { _stop = true; }
    uint32_t getCoreId() const { return dev->getCurrentCoreId(); }
    bool run(uint32_t coreId);
};
