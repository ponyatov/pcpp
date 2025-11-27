#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>

/// @defgroup dpdk dpdk
/// @{
#include <rte_debug.h>
#include <rte_eal.h>
#include <rte_lcore.h>
/// @}

/// @defgroup main main
/// @{
extern int main(int argc, char *argv[]);
extern void arg(int argc, char *argv);
/// @}

/// @defgroup syntax syntax
/// @{
#include <readline/history.h>
#include <readline/readline.h>

#include <csignal>

/// @name readline
/// @{
extern void signal_handler(int sig);  ///< UNIX signals handler
extern void rl_init();                ///< run at @ref main start
extern void rl_fini();                ///< cleanup (hump history, etc)
extern int rl_repl();                 ///< REPL loop
/// @}

/// @name lexer
/// @{
extern int yylex();
extern int yylineno;
extern char *yytext;
extern char *yyfile;
extern FILE *yyin;
/// @}

/// @name parser
/// @{
extern int yyparse();
extern void yyerror(std::string msg);
/// @}

#include "pcpp.yacc.hpp"
/// @}
