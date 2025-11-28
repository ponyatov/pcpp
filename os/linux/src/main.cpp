#include "app.hpp"

__attribute__((weak)) int main(int argc, char *argv[]) {
    arg(0, argv[0]);
    RL::init();
    Watch::init(argc, argv);
    Net::init(argc, argv);
    setup(argc, argv);
    for (int i = 1; i < argc; i++) arg(i, argv[i]);
    assert(background = new std::thread(loop));
    return RL::repl();
}

static void restart_on_linux(int ret) {
    char pname[0x100];
    ssize_t plen = readlink("/proc/self/exe", pname, sizeof(pname) - 1);
    assert(plen != -1);
    pname[plen] = '\0';
    pid_t pid = fork();
    char *args[] = {pname, nullptr};
    if (pid == 0) {  // child
        execv(pname, args);
    } else if (pid > 0) {  // parent
        stop = true;
        background->join();
        exit(ret);
    }
}
