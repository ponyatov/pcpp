#include "app.hpp"

char* yyfile = nullptr;

void yyerror(std::string msg) {
    std::cerr << "\n\n"
              << yyfile << ':' << yylineno << ' ' << msg << " [" << yytext
              << "]\n\n"
              << std::flush;
    exit(-1);
}
