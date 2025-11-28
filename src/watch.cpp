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
