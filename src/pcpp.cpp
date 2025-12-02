#include "pcpp.hpp"

extern int main(int argc, char* argv[]) {  //
    arg(0, argv[0]);
    Watch::init(argc, argv);
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
    }
    Dev::init(argc, argv);
    while (!Dev::_stop)  //
        std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}

void arg(int argc, char* argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << "]\n";
}

void Watch::watch(char* argv) {  //
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, argv, IN_CLOSE_WRITE | IN_ATTRIB);
    char buf[1024];
    read(fd, buf, sizeof(buf));
    inotify_rm_watch(fd, wd);
    Dev::stop();
    exit(1);
}

std::vector<std::thread*> Watch::thread;

void Watch::init(int argc, char* argv[]) {  //
    for (int i = 0; i < argc; i++) {        //
        thread.push_back(new std::thread(Watch::watch, argv[i]));
    }
}

pcpp::DpdkDevice* Dev::dev = nullptr;
pcpp::CoreMask Dev::coreMaskToUse = pcpp::getCoreMaskForAllMachineCores();

void Dev::init(int argc, char* argv[]) {  //
    Dev::stop();
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
    Dev::workers.push_back(new Send(dev));
    pcpp::DpdkDeviceList::getInstance().startDpdkWorkerThreads(0b110,
                                                               Dev::workers);
}

void Dev::stop() {
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

bool Send::run(uint32_t coreId) {  //
    _coreId = coreId;
    pcpp::EthLayer eth_layer(sendMac, recvMac, PCPP_ETHERTYPE_IP);
    packet.addLayer(&eth_layer);
    packet.computeCalculateFields();
    pcpp::MBufRawPacket* mbufArr[64] = {};
    for (int i = 0; i < 64; i++) {  //
        auto raw = packet.getRawPacket();
        auto mbuf = new pcpp::MBufRawPacket();
        mbuf->initFromRawPacket(raw, dev);
        mbufArr[i] = mbuf;
    }
    while (!_stop) {  //
        // dev->sendPacket(packet);
        dev->sendPackets(mbufArr, 64, 0);
        // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    return true;
}

#define M (1024. * 1024.)

bool Stat::run(uint32_t coreId) {  //
    _coreId = coreId;
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
    return true;
}
