#include "pcpp.hpp"

extern int main(int argc, char* argv[]) {
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) arg(i, argv[i]);
    Dev::init(argc, argv);
    Watch::init(argc, argv);
    for (;;) std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}

void arg(int argc, char* argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << ">\n";
}
