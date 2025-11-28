#pragma once
/// @defgroup watch watch
/// @brief watch file changes & restart

#include "app.hpp"

/// @ingroup main
/// @{
extern void signal_handler(int sig);        ///< UNIX signals handler
extern void watch(int argc, char *argv[]);  ///< start binary/script watchers
/// @}
