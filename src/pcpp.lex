%{
    #include "pcpp.hpp"
%}

%option noyywrap yylineno

%%
";"[^\n]*       {}                      // line comment
[ \t\r\n]+      {}                      // drop spaces
.               { yyerror(yytext); }    // any undetected char

%%
char* yyfile = nullptr;
