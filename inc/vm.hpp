#pragma once

/// command opcode
enum class op {
    nop = 0x00,   ///< @ref nop `( -- )` empty command
    halt = 0xFF,  ///< @ref halt `( -- )` stop system
};

extern void nop();
extern void halt();
