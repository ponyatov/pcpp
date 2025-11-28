#pragma once
/// @defgroup cli cli
/// @ingroup lib
/// @brief CLI: command line interface (REPL)
/// @{

#include "rl.hpp"

extern void cli(char *filename);  ///< process script file

/// @name number parsers
/// @{
extern float num(char *s);  ///< @returns float
extern int dec(char *s);    ///< @returns decimal
extern int hex(char *s);    ///< @returns hexadecimal
extern int oct(char *s);    ///< @returns octal
extern int bin(char *s);    ///< @returns binary
/// @}

/// @}
