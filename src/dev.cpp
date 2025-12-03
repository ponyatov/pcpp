
#include "app.hpp"

pcpp::DpdkDevice* Dev::dev = nullptr;
pcpp::CoreMask Dev::coreMaskToUse = pcpp::getCoreMaskForAllMachineCores();

void Dev::init(int argc, char* argv[]) {
    Dev::signal();
    assert(pcpp::DpdkDeviceList::initDpdk(coreMaskToUse, MBufPoolSize));
    // , 0, 0, argc, argv, APP));
    assert(dev = pcpp::DpdkDeviceList::getInstance().getDeviceByPort(0));
    assert(dev->getMtu() >= Dev::MTU);
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

std::vector<pcpp::DpdkWorkerThread*> Dev::workers;

void Dev::signal() {
    pcpp::ApplicationEventHandler::getInstance().onApplicationInterrupted(
        Dev::sigint, NULL);
}

void Dev::stop() {
    std::clog << "\nstop:" << dev->getDeviceName();
    int timeout = 0;
    while (Worker::active.load(std::memory_order_relaxed)) {
        std::clog << " " << Worker::active.load(std::memory_order_relaxed);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (++timeout > 2222) {
            std::clog << " aborted\n\n";
            break;
        }
    }
    std::clog << "\n";
    pcpp::DpdkDeviceList::getInstance().stopDpdkWorkerThreads();
    dev->close();
    std::clog << "\ninterrupted:" << dev->getDeviceName() << "\n";
    exit(-1);
}

void Dev::sigint(void*) { stop(); }
