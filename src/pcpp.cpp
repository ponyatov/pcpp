#include "pcpp.hpp"

extern int main(int argc, char* argv[]) {  //
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
    }
    Dev::init(argc, argv);
    while (!Dev::_stop)  //
        std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}

extern void arg(int argc, char* argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << "]\n";
}

pcpp::DpdkDevice* Dev::dev = nullptr;
pcpp::CoreMask Dev::coreMaskToUse = pcpp::getCoreMaskForAllMachineCores();

void Dev::init(int argc, char* argv[]) {  //
    Dev::on_close();
    assert(pcpp::DpdkDeviceList::initDpdk(coreMaskToUse, MBUF_POOL_SIZE));
    assert(dev = pcpp::DpdkDeviceList::getInstance().getDeviceByPort(0));
    std::clog << "dev: " << dev->getDeviceName()           //
              << " id:" << dev->getDeviceId()              //
              << " mac:" << dev->getMacAddress()           //
              << " pci:" << dev->getPciAddress()           //
              << " pmd:" << dev->getPMDName()              //
              << " tx:" << dev->getTotalNumOfTxQueues()    //
              << " rx:" << dev->getTotalNumOfRxQueues()    //
              << " mbuf:" << dev->getAmountOfMbufsInUse()  //
              << '/' << dev->getAmountOfFreeMbufs()        //
              << "\n";
    assert(dev->openMultiQueues(1, 1));
    Dev::workers.push_back(new Stat(dev));
    pcpp::DpdkDeviceList::getInstance().startDpdkWorkerThreads(0b10,
                                                               Dev::workers);
}

void Dev::on_close() {
    pcpp::ApplicationEventHandler::getInstance().onApplicationInterrupted(
        Dev::onApplicationInterrupted, NULL);
}

bool Dev::_stop = false;

void Dev::onApplicationInterrupted(void*) {  //
    pcpp::DpdkDeviceList::getInstance().stopDpdkWorkerThreads();
    dev->close();
    std::clog << "\ninterrupted:" << dev->getDeviceName() << "\n";
    _stop = true;
}

std::vector<pcpp::DpdkWorkerThread*> Dev::workers;

bool Stat::run(uint32_t coreId) {  //
    _coreId = coreId;
    for (uint n = 0; !_stop; n++) {
        dev->getStatistics(stats);

        std::clog << "stat:" << n                                      //
                  << " core:" << getCoreId()                           //
                  << " mac:" << dev->getMacAddress()                   //
                  << " mbuf:" << dev->getAmountOfMbufsInUse()          //
                  << '/' << dev->getAmountOfFreeMbufs()                //
                  << " packets:" << stats.aggregatedRxStats.packets    //
                  << '/' << stats.aggregatedTxStats.packets            //
                  << " pps:" << stats.aggregatedRxStats.packetsPerSec  //
                  << '/' << stats.aggregatedTxStats.packetsPerSec      //
                  << " bytes:" << stats.aggregatedRxStats.bytes        //
                  << '/' << stats.aggregatedTxStats.bytes              //
                  << " bps:" << stats.aggregatedRxStats.bytesPerSec    //
                  << '/' << stats.aggregatedTxStats.bytesPerSec        //
                  << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return true;
}
