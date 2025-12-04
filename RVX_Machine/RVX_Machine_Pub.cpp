#ifndef _RVX_MACHINE_PUB_CPP_
#define _RVX_MACHINE_PUB_CPP_

#include "RVX_Machine.h"

RVX_Machine::RVX_Machine()
{
}

RVX_Machine::~RVX_Machine()
{
}

bool RVX_Machine::run()
{
    // Fetch instruction
    inst = *(uint32_t *)&InstMem[pc];

    // Decode and Execute
    bool status = RV32I();

    // Update PC
    if (jumpEn)
    {
        pc = jumpAddr;
        jumpEn = false;
    }
    else
    {
        pc += 4;
    }

    return status;
}
uint32_t *RVX_Machine::getRegfile()
{
    return regfile;
}
uint8_t *RVX_Machine::getInstMem()
{
    return InstMem;
}
uint8_t *RVX_Machine::getDataMem()
{
    return DataMem;
}
uint32_t RVX_Machine::getPC()
{
    return pc;
}

#endif // _RVX_MACHINE_PUB_CPP_