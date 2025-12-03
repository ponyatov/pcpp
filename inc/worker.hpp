#pragma once

#include "app.hpp"

/// @brief common worker model
class Worker : public pcpp::DpdkWorkerThread {
   protected:
    uint32_t _coreId;
    bool _stop;

   public:
    pcpp::DpdkDevice* dev;
    static uint32_t coreMask;
    static std::vector<pcpp::DpdkWorkerThread*> threads;  ///<
    static std::atomic<int> active;  ///< active workers count
    Worker(pcpp::DpdkDevice* dev);   ///<
    void stop() { _stop = true; }
    uint32_t getCoreId() const { return dev->getCurrentCoreId(); }
    bool run(uint32_t coreId);
    bool terminate();
};
