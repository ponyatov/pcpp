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
