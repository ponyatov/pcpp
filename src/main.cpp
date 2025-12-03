#include "app.hpp"

extern int main(int argc, char* argv[]) {
    arg(0, argv[0]);
    setup(argc, argv);
    for (int i = 1; i < argc; i++) arg(i, argv[i]);
    Dev::init(argc, argv);
    Watch::init(argc, argv);
    return loop();
}

void arg(int argc, char* argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << ">\n";
}

void setup(int argc, char* argv[]) {  //
    std::cout << "setup: ok\n";
}

int loop() {  //
    std::cout << "loop: ";
    while (Worker::active.load(std::memory_order_relaxed)) {
        // std::cout << ".";
        std::this_thread::sleep_for(std::chrono::milliseconds(111));
    }
    std::cout << "\n";
    return 0;
}
