#include "app.hpp"


__attribute__((weak)) void cli(char* filename) {
    yyfile = filename;
    assert(yyin = fopen(yyfile, "r"));
    yyparse();
    fclose(yyin);
    yyfile = nullptr;
}
