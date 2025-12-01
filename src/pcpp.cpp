#include "pcpp.hpp"

extern int main(int argc, char* argv[]) {  //
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
    }
    init(argc, argv);
    return 0;
}

extern void arg(int argc, char* argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << "]\n";
}

extern void init(int argc, char* argv[]) {  //
    pcpp::CoreMask coreMaskToUse(0x1);
    assert(pcpp::DpdkDeviceList::initDpdk(coreMaskToUse, MBUF_POOL_SZ));
}
