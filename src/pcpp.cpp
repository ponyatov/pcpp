#include "pcpp.hpp"

extern int main(int argc, char* argv[]) {  //
    arg(0, argv[0]);
    Watch::init(argc, argv);
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
    }
    // return 0;
    Dev::init(argc, argv);
    while (!Dev::_stop)  //
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
    assert(pcpp::DpdkDeviceList::initDpdk(coreMaskToUse, MBufPoolSize));
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
