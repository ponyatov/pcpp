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

extern int yylex();
extern char *yytext;
extern char *yyfile;
extern FILE *yyin;
extern int yyparse();
extern void yyerror(std::string msg);
extern int yylineno;

#include "pcpp.yacc.hpp"
/// @}
