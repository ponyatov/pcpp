
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
    Worker::threads.push_back(new Stat(dev));
    coreMask = (coreMask << 1) | 0b10;
    for (auto g : config.groups) {
        Worker::threads.push_back(new Group(dev, g));
        coreMask = (coreMask << 1) | 0b10;
    }
    pcpp::DpdkDeviceList::getInstance().startDpdkWorkerThreads(  //
        coreMask, Worker::threads);
}

void Dev::signal() {
    pcpp::ApplicationEventHandler::getInstance().onApplicationInterrupted(
        Dev::sigint, NULL);
}

void Dev::stop() {
    std::clog << "\nstop:" << dev->getDeviceName();
    pcpp::DpdkDeviceList::getInstance().stopDpdkWorkerThreads();
    assert(!Worker::active.load(std::memory_order_relaxed));
    dev->close();
    std::clog << " closed\n\n" << dev->getDeviceName() << "\n";
    exit(-1);
}

void Dev::sigint(void*) { stop(); }
