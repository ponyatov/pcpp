#pragma once
/// @defgroup watch watch
/// @brief watch file changes & restart

#include "app.hpp"

/// @ingroup main
/// @{
class Watch {
    static void signal(int sig);                ///< UNIX signals handler
    static void file(char *filename);           //
    static std::vector<std::thread *> threads;  //

   public:                                     //
    static void init(int argc, char *argv[]);  ///< start binary/script watchers
};
/// @}
