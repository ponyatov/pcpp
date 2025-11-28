#pragma once

#include <csignal>

/// @defgroup watch watch
/// @brief watch file changes & restart
/// @ingroup main
/// @{

extern void signal_handler(int sig);  ///< UNIX signals handler
/// @}
