#pragma once

#include <sys/inotify.h>

class Watch {
    static std::vector<std::thread*> thread;
    static void watch(char* argv);

   public:
    static void init(int argc, char* argv[]);
};
