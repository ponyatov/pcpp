#include <csignal>

#include "app.hpp"

void Watch::watch(char* argv) {  //
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, argv, IN_CLOSE_WRITE | IN_ATTRIB);
    char buf[1024];
    read(fd, buf, sizeof(buf));
    inotify_rm_watch(fd, wd);
    Dev::stop();
}

std::vector<std::thread*> Watch::thread;

void Watch::init(int argc, char* argv[]) {  //
    for (int i = 0; i < argc; i++) {        //
        thread.push_back(new std::thread(Watch::watch, argv[i]));
    }
}
