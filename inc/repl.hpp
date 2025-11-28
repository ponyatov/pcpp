#pragma once
/// @defgroup repl repl
/// @brief REPL: command line interface
/// @{

#include <readline/history.h>
#include <readline/readline.h>

/// @name readline
/// @{
extern void rl_init();  ///< run at @ref main start
extern void rl_fini();  ///< cleanup (hump history, etc)
extern int rl_repl();   ///< REPL loop
/// @}

/// @}
