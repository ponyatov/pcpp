#include "app.hpp"

Stat* Stat::single;

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
                  << " packets:" << stats.aggregatedTxStats.packets       //
                  << " pps:" << stats.aggregatedTxStats.packetsPerSec     //
                  << " mbytes:" << stats.aggregatedTxStats.bytes / M      //
                  << " mbps:" << stats.aggregatedTxStats.bytesPerSec / M  //
                  << "\n";

        const std::string request_str = "Hello";
        auto buf = zmq::buffer(request_str);
        zmq::message_t request(buf);
        // MQ::test->sock()->send(request, zmq::send_flags::none);

        // const std::string request_str = "Hello";
        // zmq::message_t request(zmq::buffer(request_str));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
