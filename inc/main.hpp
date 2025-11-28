#pragma once
/// @defgroup main main
/// @{
extern int main(int argc, char *argv[]);    ///< POSIX entry point
extern void arg(int argc, char *argv);      ///< print command line argument
extern void setup(int argc, char *argv[]);  ///< generic setup
extern void loop();                         ///< event loop
extern std::thread *background;             ///< thread for @ref loop
extern bool stop;                           ///< @ref loop stop flag

/// @}
