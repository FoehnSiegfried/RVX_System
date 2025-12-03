#ifndef _RVX_RV32I_CPP_
#define _RVX_RV32I_CPP_

#include <stdint.h>
#include "RCSignals.h"
#include "../Lib/Map_Lib/Map.h"

#define OP_R 0b0110011
#define OP_I 0b0010011
#define OP_IL 0b00000011
#define OP_IS 0b0100011
#define OP_IJ 0b1100111
#define OP_IE 0b1110011
#define OP_S 0b0100011
#define OP_B 0b1100011
#define OP_U 0b0110111
#define OP_UA 0b0010111
#define OP_J 0b1101111

//识别是否是RV32I指令集的指令
bool identifyRV32I(uint32_t inst)
{
    uint8_t opcode = inst & 0x7F;
    switch (opcode)
}

#endif // _RVX_RV32I_CPP_