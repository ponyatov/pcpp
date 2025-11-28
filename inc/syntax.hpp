#pragma once
/// @defgroup syntax syntax
/// @ingroup command/syntax parser
/// @{

/// @name lexer
/// @{
extern int yylex();                    ///< lexer
extern int yylineno;                   ///< line number
extern char *yytext;                   ///< lexeme (token) string value
extern char *yyfile;                   ///< current file name
extern FILE *yyin;                     ///< file handler
/// @}

/// @name parser
/// @{
extern void parse(char *);             ///< parse string
extern int yyparse();                  ///< parser
extern void yyerror(std::string msg);  ///< syntax error callback
#include "repl.yacc.hpp"
/// @}
