#pragma once
/// @defgroup rl rl
/// @brief readline
/// @ingroup cli
/// @{

#include <readline/history.h>
#include <readline/readline.h>

class RL {
   public:
    static void init();  ///< run at @ref main start
    static void fini();  ///< cleanup (hump history, etc)
    static int repl();   ///< REPL loop
    static int counter;  ///< commands counter
};
/// @}
