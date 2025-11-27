%{
    #include "pcpp.hpp"
%}

%defines %union { char c; }

%%
ini:

%%
void yyerror(std::string msg) {
    std::cerr << "\n\n"
              << yyfile << ':' << yylineno << ' ' << msg << " [" << yytext
              << "]\n\n";
    exit(-1);
}
