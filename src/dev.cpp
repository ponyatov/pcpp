
#include "app.hpp"

pcpp::DpdkDevice* Dev::dev = nullptr;
pcpp::CoreMask Dev::coreMaskToUse = pcpp::getCoreMaskForAllMachineCores();

uint16_t Dev::MTU = 0;

void Dev::init(int argc, char* argv[]) {
    assert(pcpp::DpdkDeviceList::initDpdk(coreMaskToUse, MBufPoolSize));
    // , 0, 0, argc, argv, APP));
    pcpp::ApplicationEventHandler::getInstance().onApplicationInterrupted(
        Dev::sigint, NULL);
    assert(dev = pcpp::DpdkDeviceList::getInstance().getDeviceByPort(0));
    // assert(Dev::MTU = dev->getMtu());
    Dev::MTU = 1400;
    assert(Dev::MTU <= Dev::MTU_MAX);
    std::clog << "dev: " << dev->getDeviceName()           //
              << " id:" << dev->getDeviceId()              //
              << " mac:" << dev->getMacAddress()           //
              << " pci:" << dev->getPciAddress()           //
              << " pmd:" << dev->getPMDName()              //
              << " tx:" << dev->getTotalNumOfTxQueues()    //
              << " rx:" << dev->getTotalNumOfRxQueues()    //
              << " mbuf:" << dev->getAmountOfMbufsInUse()  //
              << '/' << dev->getAmountOfFreeMbufs()        //
              << " mtu:" << dev->getMtu()                  //
              << "\n";
    assert(dev->openMultiQueues(1, 1));
    //
    new Stat(dev);
    for (auto g : config.groups) new Group(dev, g);
    //
    pcpp::DpdkDeviceList::getInstance().startDpdkWorkerThreads(  //
        Worker::coreMask, Worker::threads);
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
