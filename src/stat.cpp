#include "app.hpp"

#define M (1024. * 1024.)

bool Stat::run(uint32_t coreId) {  //
    assert(Worker::run(coreId));
    for (uint n = 0; !_stop; n++) {
        dev->getStatistics(stats);

        std::clog << "stat:" << n                                         //
                  << " core:" << getCoreId()                              //
                  << " mac:" << dev->getMacAddress()                      //
                  << " mbuf:" << dev->getAmountOfMbufsInUse()             //
                  << '/' << dev->getAmountOfFreeMbufs()                   //
                  << " packets:" << stats.aggregatedRxStats.packets       //
                  << '/' << stats.aggregatedTxStats.packets               //
                  << " pps:" << stats.aggregatedRxStats.packetsPerSec     //
                  << '/' << stats.aggregatedTxStats.packetsPerSec         //
                  << " mbytes:" << stats.aggregatedRxStats.bytes / M      //
                  << '/' << stats.aggregatedTxStats.bytes / M             //
                  << " mbps:" << stats.aggregatedRxStats.bytesPerSec / M  //
                  << '/' << stats.aggregatedTxStats.bytesPerSec / M       //
                  << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
