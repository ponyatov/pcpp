#include "app.hpp"

__attribute__((weak)) void arg(int argc, char *argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << ">\n";
    if (argc) cli(argv);
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
                t->tm_sec, APP, RL::counter);
        rl_set_prompt(_prompt);
        rl_redisplay();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    exit(0);
}

__attribute__((weak)) void restart(int ret) {
    stop = true;
    background->join();
    exit(ret);
}
