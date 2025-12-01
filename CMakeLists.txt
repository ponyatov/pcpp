# We need 3.12 or later, so that we can set policy CMP0074; see below.
cmake_minimum_required(VERSION 3.11)
get_filename_component(CMAKE_PROJECT_NAME ${CMAKE_SOURCE_DIR} NAME_WE)

set(PCAPPP_VERSION "25.05")
project(
  ${CMAKE_PROJECT_NAME}
  VERSION ${PCAPPP_VERSION}
  DESCRIPTION "PcapPlusPlus is a multiplatform C++ library for capturing, parsing and crafting of network packets."
  LANGUAGES CXX C ASM
  HOMEPAGE_URL "https://pcapplusplus.github.io/"
)

include(version)  # binary files naming by version & git branch/hash
include(src)      # scan project for source code files

message("-- |")
message("-- | toolchain: " ${CMAKE_CXX_COMPILER} " @ " ${CMAKE_TOOLCHAIN_FILE})
message("-- |      host: " ${CMAKE_HOST_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_VERSION})
message("-- |    target: " "hw:" ${HW} " cpu:" ${CPU} " arch:" ${ARCH} " os:" ${OS})
message("-- |   startup: " "${S}")
message("-- |    linker: " "${LD}")
message("-- |    binary: " "${CMAKE_INSTALL_PREFIX}/${BIN_OUTPUT_NAME}${CMAKE_EXECUTABLE_SUFFIX}")
message("-- |")
if(PCAP_FOUND)
message("-- | PCAP: ${PCAP_VERSION}")
endif()
if(DPDK_FOUND)
message("-- | DPDK: ${DPDK_VERSION}")
endif()

add_executable(${CMAKE_PROJECT_NAME}
    ${C}  ${H}          # C/C++ source
    ${S}  ${LD}         # embedded/lowlevel
    ${CP} ${HP}         # parsers
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    -Wl,--start-group ${L} -Wl,--end-group
) # -static

include(install) # target install
