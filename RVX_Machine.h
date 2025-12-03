#ifndef _RVX_MACHINE_H_
#define _RVX_MACHINE_H_

#include <stdint.h>

#include "RCSignals.h"
#include "RVX_RV32I.cpp"

#define INST_MEM_SIZE 1024
#define DATA_MEM_SIZE 1024

class RVX_Machine
{
private:
    uint32_t regfile[32];
    uint8_t InstMem[INST_MEM_SIZE];
    uint8_t DataMem[DATA_MEM_SIZE];

    uint32_t pc = 0x00000000;

public:
    RVX_Machine();
    ~RVX_Machine();
    void run();
    uint32_t *getRegfile();
    uint8_t *getInstMem();
    uint8_t *getDataMem();
    uint32_t getPC();
};

#include "RVX_Machine_Pub.cpp"
#include "RVX_Machine_Pri.cpp"

#endif // _RVX_MACHINE_H_