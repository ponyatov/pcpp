include(FindPackageHandleStandardArgs)

# ~~~
# - Try to find READLINE include dirs and libraries
#
# Find the READLINE includes and client library
# This module defines:
#  READLINE_FOUND, If false, do not try to use READLINE.
#  READLINE_INCLUDE_DIRS, where to find rte_config.h and rte_version.h
#  READLINE_LIBRARIES, the libraries needed by a READLINE user
#  READLINE_CFLAGS_OTHER, the compile flags to use
#  READLINE_VERSION, the version of the library
# ~~~

find_package(PkgConfig REQUIRED)
pkg_check_modules(READLINE REQUIRED readline>=8.2)

if(READLINE_FOUND)
  message("-- | READLINE: ${READLINE_VERSION}")
  add_compile_definitions(READLINE_FOUND)

  add_library(READLINE::READLINE INTERFACE IMPORTED)    

  target_include_directories(READLINE::READLINE INTERFACE ${READLINE_INCLUDE_DIRS})
  target_compile_options(READLINE::READLINE INTERFACE ${READLINE_CFLAGS_OTHER})
  target_link_libraries(READLINE::READLINE INTERFACE ${READLINE_LIBRARIES})

endif()

# find_library(READLINE_LIBRARY
#     NAMES readline
#     HINTS ${READLINE_ROOT} /usr/local/lib/* /usr/lib/*
#     PATH_SUFFIXES lib
# )

# find_path(READLINE_INCLUDE_DIR
#     NAMES readline.h history.h
#     HINTS ${READLINE_ROOT} /usr/local/include /usr/include
#     PATH_SUFFIXES readline
# )

# find_package_handle_standard_args(READLINE DEFAULT_MSG
#     READLINE_LIBRARY
#     READLINE_INCLUDE_DIR
# )

# if(READLINE_FOUND)
#     list(APPEND LIBS ${READLINE_LIBRARY})
# endif()

# if(READLINE_FOUND AND NOT TARGET READLINE::READLINE)
#     add_library(READLINE::READLINE SHARED IMPORTED)
#     set_target_properties(READLINE::READLINE PROPERTIES
#         IMPORTED_LOCATION "${READLINE_LIBRARY}"
#         INTERFACE_INCLUDE_DIRECTORIES "${READLINE_INCLUDE_DIR}"
#     )
# endif()
