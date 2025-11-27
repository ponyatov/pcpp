%{
    #include "pcpp.hpp"
%}

%option noyywrap yylineno

%%

.               { yyerror(yytext); }

%%
char* yyfile = nullptr;
