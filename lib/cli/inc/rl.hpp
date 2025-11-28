#pragma once
/// @defgroup rl rl
/// @brief readline
/// @ingroup cli
/// @{

#include <readline/history.h>
#include <readline/readline.h>

extern void rl_init();        ///< run at @ref main start
extern void rl_fini();        ///< cleanup (hump history, etc)
extern int rl_repl();         ///< REPL loop
/// @}
