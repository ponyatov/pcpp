#include "app.hpp"

void rl_init() {
    std::signal(SIGINT, signal_handler);   // \ register dignals
    std::signal(SIGTERM, signal_handler);  // /
    printf("PID: %d\n", getpid());         // for debug: kill -SIGTERM <pid>
    rl_readline_name = APP;
    rl_bind_key('\t', rl_complete);       // filename completion (by default)
    read_history("tmp/" APP ".history");  // load
    stifle_history(10);                   // keep last N commands
}

void rl_fini() {
    write_history("tmp/" APP ".history");  // save/create if not exists
}

int rl_repl() {
    char *input;
    while ((input = readline(APP "> ")) != nullptr) {
        std::string line(input);
        std::clog << "input:" << line << '\n';
        if (!line.empty()) { add_history(input); }
        free(input);
    }  // stops on Ctrl+D (EOF)
    rl_fini();
    return 0;
}
