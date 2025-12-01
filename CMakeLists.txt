# We need 3.12 or later, so that we can set policy CMP0074; see below.
cmake_minimum_required(VERSION 3.12)
get_filename_component(CMAKE_PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME_WE)
project(${CMAKE_PROJECT_NAME} VERSION 25.05 LANGUAGES C CXX ASM)

# set(PCAPPP_VERSION "25.05")

include(version)  # binary files naming by version & git branch/hash

message("-- |")
message("-- | toolchain: " ${CMAKE_CXX_COMPILER} " @ " ${CMAKE_TOOLCHAIN_FILE})
message("-- |      host: " ${CMAKE_HOST_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_VERSION})
message("-- |    target: " "hw:" ${HW} " cpu:" ${CPU} " arch:" ${ARCH} " os:" ${OS})
message("-- |   startup: " "${S}")
message("-- |    linker: " "${LD}")
message("-- |    binary: " "${CMAKE_INSTALL_PREFIX}/${BIN_OUTPUT_NAME}${CMAKE_EXECUTABLE_SUFFIX}")
message("-- |      wasm: " "${WASM}")
message("-- |    kaitai: " "${KSY}")
message("-- |")

include(install) # target install
