
#include "pcpp.hpp"

pcpp::DpdkDevice* Dev::dev = nullptr;
pcpp::CoreMask Dev::coreMaskToUse = pcpp::getCoreMaskForAllMachineCores();

void Dev::init(int argc, char* argv[]) {
    Dev::signal();
    assert(pcpp::DpdkDeviceList::initDpdk(coreMaskToUse, MBufPoolSize, 0, 0,
                                          argc, argv, APP));
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
    uint32_t coreMask = 0;
    Dev::workers.push_back(new Stat(dev));
    coreMask = (coreMask << 1) | 0b10;
    for (auto g : config.groups) {
        Dev::workers.push_back(new Group(dev, g));
        coreMask = (coreMask << 1) | 0b10;
    }
    pcpp::DpdkDeviceList::getInstance().startDpdkWorkerThreads(coreMask,
                                                               Dev::workers);
}

bool Dev::_stop = false;

std::vector<pcpp::DpdkWorkerThread*> Dev::workers;
