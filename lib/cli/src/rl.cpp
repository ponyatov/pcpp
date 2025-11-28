#include "app.hpp"

void RL::init() {
    rl_readline_name = APP;
    rl_bind_key('\t', rl_complete);       // filename completion (by default)
    read_history("tmp/" APP ".history");  // load
    stifle_history(10);                   // keep last N commands
    rl_clear_pending_input();             // clean input
}

void RL::fini() {
    write_history("tmp/" APP ".history");  // save/create if not exists
}

int RL::counter = 0;

int RL::repl() {
    char* input;
    while ((input = readline(APP "> ")) != nullptr) {
        std::string line(input);
        std::clog << "input:" << line << '\n';
        if (!line.empty()) {
            RL::counter++;
            add_history(input);
        }
        free(input);
    }  // stops on Ctrl+D (EOF)
    RL::fini();
    return 0;
}
