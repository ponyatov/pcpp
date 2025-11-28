#include "app.hpp"

void rl_init() {
    rl_readline_name = APP;
    rl_bind_key('\t', rl_complete);       // filename completion (by default)
    read_history("tmp/" APP ".history");  // load
    stifle_history(10);                   // keep last N commands
    rl_clear_pending_input();             // clean input
}

void rl_fini() {
    write_history("tmp/" APP ".history");  // save/create if not exists
}

int rl_counter = 0;

int rl_repl() {
    char* input;
    while ((input = readline(APP "> ")) != nullptr) {
        std::string line(input);
        std::clog << "input:" << line << '\n';
        if (!line.empty()) {  //
            rl_counter++;
            add_history(input);
        }
        free(input);
    }  // stops on Ctrl+D (EOF)
    rl_fini();
    return 0;
}
