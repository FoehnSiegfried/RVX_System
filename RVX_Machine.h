#ifndef _RVX_MACHINE_H_
#define _RVX_MACHINE_H_

#include <stdint.h>

#include "../Lib/Map_Lib/Map.h"

#define INST_MEM_SIZE 1024
#define DATA_MEM_SIZE 1024

class RVX_Machine
{
private:
    uint32_t regfile[32];
    uint8_t InstMem[INST_MEM_SIZE];
    uint8_t DataMem[DATA_MEM_SIZE];
    uint32_t pc = 0x00000000;
    bool jumpEn=false;
    uint32_t jumpAddr=0x00000000;
    uint32_t inst = 0x00000013;

    //RV32I
    bool RV32I();
    void RV32I_Type_R();
    void RV32I_Type_I();
    void RV32I_Type_S();
    void RV32I_Type_B();
    void RV32I_Type_U();
    void RV32I_Type_J();

public:
    RVX_Machine();
    ~RVX_Machine();
    bool run();
    uint32_t *getRegfile();
    uint8_t *getInstMem();
    uint8_t *getDataMem();
    uint32_t getPC();
};

#include "RVX_Machine_Pub.cpp"
#include "RVX_Machine_Pri.cpp"
#include "RVX_RV32I.cpp"

#endif // _RVX_MACHINE_H_