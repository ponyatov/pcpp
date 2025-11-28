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
    char _prompt[0x10];
    while (!stop) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        sprintf(_prompt, "%02d:%02d:%02d %s[%i]> ", t->tm_hour, t->tm_min,
                t->tm_sec, APP, rl_counter);
        rl_set_prompt(_prompt);
        rl_redisplay();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    exit(0);
}
