#include "pcpp.hpp"

void rl_init() {
    rl_readline_name = APP;
    rl_bind_key('\t', rl_complete);       // filename completion (by default)
    read_history("tmp/" APP ".history");  // load
    stifle_history(10);                   // keep last N commands
}

void rl_fini() {
    write_history("tmp/" APP ".history");  // save/create if not exists
}

int repl() {
    rl_init();
    char *input;
    while ((input = readline(APP "> ")) != nullptr) {
        std::string line(input);
        std::clog << "input:" << line << '\n';
        if (!line.empty()) { add_history(input); }
        free(input);
    }
    rl_fini();
    return 0;
}

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

int main(int argc, char *argv[]) {  //
    arg(0, argv[0]);
    std::signal(SIGINT, signal_handler);
    std::cout << "\nrte:" << rte_eal_init(argc, argv) << '\n';
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
        yyfile = argv[i];
        assert(yyin = fopen(yyfile, "r"));
        yyparse();
        fclose(yyin);
        yyfile = nullptr;
    }
    return repl();
}

void arg(int argc, char *argv) {  //
    std::clog << "arg[" << argc << "] = <" << argv << ">\n";
}
