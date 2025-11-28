#include "app.hpp"

__attribute__((weak)) void cli(char* filename) {
    yyfile = filename;
    assert(yyin = fopen(yyfile, "r"));
    yylineno = 1;
    yyparse();
    yylineno = 0;
    fclose(yyin);
    yyfile = nullptr;
}
