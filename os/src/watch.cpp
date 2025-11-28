#include "app.hpp"

void signal_handler(int sig) {  //
    fprintf(stderr, "\n\nsignal:%i ", sig);
    rl_fini();
    switch (sig) {
        case SIGINT:  // Ctrl+C
            fprintf(stderr, "SIGINT (Ctrl+C)\n\n");
            exit(0);
        case SIGTERM:
            fprintf(stderr, "SIGTERM\n\n");
            exit(0);
        case SIGHUP:
            fprintf(stderr, "SIGHUP\n\n");
            exit(-1);
        case SIGQUIT:
            fprintf(stderr, "SIGQUIT\n\n");
            exit(-1);
        default:
            fprintf(stderr, "bad signal\n\n");
            exit(-1);
    }
}

static void _watch(int argc, char *argv) {
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, argv, IN_CLOSE_WRITE | IN_ATTRIB);
    char buf[1024];
    read(fd, buf, sizeof(buf));
    inotify_rm_watch(fd, wd);
    stop = true;
    background->join();
    exit(1);
}

static std::vector<std::thread *> _watch_t;

void watch(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++)
        _watch_t.push_back(new std::thread(_watch, i, argv[i]));
}
