# file(GLOB LD -> cmake/any_toolchain.cmake

file(GLOB S
    RELATIVE ${CMAKE_SOURCE_DIR}
    src/*.s
    # cross
    hw/${HW}/*.s
    hw/${HW}/src/*.s
    cpu/${CPU}/src/*.s
    arch/${ARCH}/src/*.s
    # lib
    lib/src/*.s lib/*/src/*.s
)

file(GLOB C
    RELATIVE ${CMAKE_SOURCE_DIR}
    src/*.c*
    # cross
      hw/src/*.c*   hw/${HW}/src/*.c*
     cpu/src/*.c*  cpu/${CPU}/src/*.c*
    arch/src/*.c* arch/${ARCH}/src/*.c*
      os/src/*.c*   os/${OS}/src/*.c*
    # lib
    lib/src/*.c* lib/*/src/*.c*
)

file(GLOB H
    RELATIVE ${CMAKE_SOURCE_DIR}
    inc/*.h*
    # cross
      hw/inc/*.h*   hw/${HW}/inc/*.h*
     cpu/inc/*.h*  cpu/${CPU}/inc/*.h*
    arch/inc/*.h* arch/${ARCH}/inc/*.h*
      os/inc/*.h*   os/${OS}/inc/*.h*
    # lib
    lib/inc/*.h* lib/*/inc/*.h*
    # cross
      hw/inc   hw/${HW}/inc
     cpu/inc  cpu/${CPU}/inc
    arch/inc arch/${ARCH}/inc
      os/inc   os/${OS}/inc
    # lib
    lib/inc lib/*/inc
)

file(GLOB INC
    RELATIVE ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    inc src
)
include_directories(${INC})
