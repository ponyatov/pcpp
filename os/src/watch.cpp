#include "app.hpp"

void Watch::signal(int sig) {  //
    fprintf(stderr, "\n\nsignal:%i ", sig);
    rl_fini();
    switch (sig) {
        case SIGINT:  // Ctrl+C
            fprintf(stderr, "SIGINT (Ctrl+C)\n\n");
            exit(sig);
        case SIGTERM:
            fprintf(stderr, "SIGTERM\n\n");
            exit(sig);
        case SIGHUP:
            fprintf(stderr, "SIGHUP\n\n");
            restart(sig);
        case SIGQUIT:
            fprintf(stderr, "SIGQUIT\n\n");
            exit(sig);
        default:
            fprintf(stderr, "bad signal\n\n");
            exit(sig);
    }
}

void Watch::file(char *filename) {
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, filename, IN_CLOSE_WRITE | IN_ATTRIB);
    char buf[1024];
    read(fd, buf, sizeof(buf));
    inotify_rm_watch(fd, wd);
    stop = true;
    background->join();
    exit(1);
}

std::vector<std::thread *> Watch::threads;

void Watch::init(int argc, char *argv[]) {
    printf("PID: %d\n", getpid());       // for debug: kill -SIGTERM <pid>
    std::signal(SIGINT, Watch::signal);  // register signals
    std::signal(SIGTERM, Watch::signal);
    std::signal(SIGHUP, Watch::signal);
    for (int i = 0; i < argc; i++)
        threads.push_back(new std::thread(Watch::file, argv[i]));
}
