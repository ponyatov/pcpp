#pragma once
/// @defgroup syntax syntax
/// @ingroup command/syntax parser
/// @{

/// @name lexer
/// @{
extern int yylex();                    ///< lexer (`flex`)
extern int yylineno;                   ///< line number
extern char *yytext;                   ///< lexeme (token) string value
extern char *yyfile;                   ///< current file name
extern FILE *yyin;                     ///< script file handler
/// @}

/// @name parser
/// @{
extern void parse(char *);             ///< parse string
extern int yyparse();                  ///< parser (`bison`)
extern void yyerror(std::string msg);  ///< syntax error callback
#include "cli.yacc.hpp"
/// @}
