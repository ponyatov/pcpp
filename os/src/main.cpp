#include "app.hpp"

__attribute__((weak)) int main(int argc, char *argv[]) {
    arg(0, argv[0]);
    rl_init();
#ifdef DPDK_FOUND
    std::cout << "\nrte:" << rte_eal_init(argc, argv) << '\n';
#endif
    setup(argc, argv);
    for (int i = 1; i < argc; i++) {
        arg(i, argv[i]);
        cli(argv[i]);
    }
    assert(background = new std::thread(loop));
    return rl_repl();
}

__attribute__((weak)) void arg(int argc, char *argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << ">\n";
}

__attribute__((weak)) void setup(int argc, char *argv[]) {
    std::clog << "setup: ";
    std::clog << "ok\n";
}

bool stop = false;
std::thread *background;
__attribute__((weak)) void loop() {
    std::clog << "\nloop: started\n";
    uint n = 0;
    while (!stop) {
        n++;
        sprintf(rl_prompt, "%.5i>", n);
        rl_set_prompt(rl_prompt);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    exit(0);
}
