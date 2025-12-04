#ifndef _RVX_RV32I_CPP_
#define _RVX_RV32I_CPP_

#include "RVX_Machine.h"

#define OP_R 0b0110011
#define OP_I 0b0010011
#define OP_IL 0b00000011
#define OP_IJ 0b1100111
#define OP_IE 0b1110011
#define OP_S 0b0100011
#define OP_B 0b1100011
#define OP_U 0b0110111
#define OP_UA 0b0010111
#define OP_J 0b1101111

bool RVX_Machine::RV32I()
{
    uint8_t opcode = inst & 0x7F;
    switch (opcode)
    {
    case OP_R:
        RV32I_Type_R();
        return true;
    case OP_I:
        RV32I_Type_I();
        return true;
    case OP_IL:
        RV32I_Type_I();
        return true;
    case OP_IJ:
        RV32I_Type_I();
        return true;
    case OP_IE:
        RV32I_Type_I();
        return true;
    case OP_S:
        RV32I_Type_S();
        return true;
    case OP_B:
        RV32I_Type_B();
        return true;
    case OP_U:
        RV32I_Type_U();
        return true;
    case OP_UA:
        RV32I_Type_U();
        return true;
    case OP_J:
        RV32I_Type_J();
        return true;
    default:
        return false;
    }
}

void RVX_Machine::RV32I_Type_R()
{
    uint8_t rd = (inst >> 7) & 0x1F;
    uint8_t funct3 = (inst >> 12) & 0x7;
    uint8_t rs1 = (inst >> 15) & 0x1F;
    uint8_t rs2 = (inst >> 20) & 0x1F;
    uint8_t funct7 = (inst >> 25) & 0x7F;

    switch (funct3)
    {
    case 0x0: // ADD, SUB
        if (funct7 == 0x00)
        {
            // ADD
            regfile[rd] = regfile[rs1] + regfile[rs2];
        }
        else if (funct7 == 0x20)
        {
            // SUB
            regfile[rd] = regfile[rs1] - regfile[rs2];
        }
        break;
    case 0x4: // XOR
        if (funct7 == 0x00)
            regfile[rd] = regfile[rs1] ^ regfile[rs2];
        break;
    case 0x6: // OR
        if (funct7 == 0x00)
            regfile[rd] = regfile[rs1] | regfile[rs2];
        break;
    case 0x7: // AND
        if (funct7 == 0x00)
            regfile[rd] = regfile[rs1] & regfile[rs2];
        break;
    case 0x1: // SLL
        if (funct7 == 0x00)
            regfile[rd] = regfile[rs1] << (regfile[rs2] & 0x1F);
        break;
    case 0x5: // SRL, SRA
        if (funct7 == 0x00)
        {
            // SRL
            regfile[rd] = regfile[rs1] >> (regfile[rs2] & 0x1F);
        }
        else if (funct7 == 0x20)
        {
            // SRA
            regfile[rd] = (int32_t)regfile[rs1] >> (regfile[rs2] & 0x1F);
        }
        break;
    case 0x2: // SLT
        if (funct7 == 0x00)
            regfile[rd] = ((int32_t)regfile[rs1] < (int32_t)regfile[rs2]) ? 1 : 0;
        break;
    case 0x3: // SLTU
        if (funct7 == 0x00)
            regfile[rd] = (regfile[rs1] < regfile[rs2]) ? 1 : 0;
        break;
    default:
        break;
    }
}
void RVX_Machine::RV32I_Type_I()
{
    uint8_t opcode = inst & 0x7F;

    uint8_t rd = (inst >> 7) & 0x1F;
    uint8_t funct3 = (inst >> 12) & 0x7;
    uint8_t rs1 = (inst >> 15) & 0x1F;

    int32_t imm = (int32_t)inst >> 20; // Sign-extended immediate

    switch (opcode)
    {
    case OP_I:
        switch (funct3)
        {
        case 0x0: // ADDI
            regfile[rd] = regfile[rs1] + imm;
            break;
        case 0x4: // XORI
            regfile[rd] = regfile[rs1] ^ imm;
            break;
        case 0x6: // ORI
            regfile[rd] = regfile[rs1] | imm;
            break;
        case 0x7: // ANDI
            regfile[rd] = regfile[rs1] & imm;
            break;
        case 0x1: // SLLI
            if ((imm >> 5) & 0x7F == 0x00)
                regfile[rd] = regfile[rs1] << (imm & 0x1F);
            break;
        case 0x5: // SRLI, SRAI
            if (((imm >> 5) & 0x7F) == 0x00)
            {
                // SRLI
                regfile[rd] = regfile[rs1] >> (imm & 0x1F);
            }
            else if (((imm >> 5) & 0x7F) == 0x20)
            {
                // SRAI
                regfile[rd] = (int32_t)regfile[rs1] >> (imm & 0x1F);
            }
            break;
        case 0x2: // SLTI
            regfile[rd] = ((int32_t)regfile[rs1] < imm) ? 1 : 0;
            break;
        case 0x3: // SLTIU
            regfile[rd] = (regfile[rs1] < (uint32_t)imm) ? 1 : 0;
            break;
        default:
            break;
        }
        break;
    case OP_IL:
        switch (funct3)
        {
        case 0x0: // LB
        {
            int8_t byte = DataMem[regfile[rs1] + imm];
            regfile[rd] = (int32_t)byte; // Sign-extend
            break;
        }
        case 0x1: // LH
        {
            int16_t halfword = *(int16_t *)&DataMem[regfile[rs1] + imm];
            regfile[rd] = (int32_t)halfword; // Sign-extend
            break;
        }
        case 0x2: // LW
        {
            int32_t word = *(int32_t *)&DataMem[regfile[rs1] + imm];
            regfile[rd] = word;
            break;
        }
        case 0x4: // LBU
        {
            uint8_t byte = DataMem[regfile[rs1] + imm];
            regfile[rd] = (uint32_t)byte; // Zero-extend
            break;
        }
        case 0x5: // LHU
        {
            uint16_t halfword = *(uint16_t *)&DataMem[regfile[rs1] + imm];
            regfile[rd] = (uint32_t)halfword; // Zero-extend
            break;
        }
        default:
            break;
        }
        break;
    case OP_IJ:
        if (funct3 == 0x0)
        {
            // JALR
            regfile[rd] = pc + 4;
            jumpAddr = (regfile[rs1] + imm) & ~1;
            jumpEn = true;
        }
        break;
    case OP_IE:
        // ECALL, EBREAK
        if ((funct3 == 0x0) || (imm == 0x0))
        {
            // ECALL
            // Handle system call (not implemented)
        }
        else if ((funct3 == 0x0) || (imm == 0x1))
        {
            // EBREAK
            // Handle breakpoint (not implemented)
        }
        break;
    default:
        break;
    }
}
void RVX_Machine::RV32I_Type_S()
{
    uint8_t funct3 = (inst >> 12) & 0x7;
    uint8_t rs1 = (inst >> 15) & 0x1F;
    uint8_t rs2 = (inst >> 20) & 0x1F;

    uint32_t imm4_0 = (inst >> 7) & 0x1F;
    int32_t imm11_5 = ((int32_t)inst >> 20) & 0xFFFFFFE0;
    int32_t imm = (int32_t)(imm11_5 | imm4_0); // Sign-extended immediate

    switch (funct3)
    {
    case 0x0: // SB
        DataMem[regfile[rs1] + imm] = regfile[rs2] & 0xFF;
        break;
    case 0x1: // SH
        *(uint16_t *)&DataMem[regfile[rs1] + imm] = regfile[rs2] & 0xFFFF;
        break;
    case 0x2: // SW
        *(uint32_t *)&DataMem[regfile[rs1] + imm] = regfile[rs2];
        break;
    default:
        break;
    }
}
void RVX_Machine::RV32I_Type_B()
{
    uint8_t funct3 = (inst >> 12) & 0x7;
    uint8_t rs1 = (inst >> 15) & 0x1F;
    uint8_t rs2 = (inst >> 20) & 0x1F;

    uint32_t imm11 = (inst >> 7) & 0x1;
    uint32_t imm4_1 = (inst >> 8) & 0xF;
    uint32_t imm10_5 = (inst >> 25) & 0x3F;
    int32_t imm12 = ((int32_t)inst >> 19) & 0xFFFFF000;
    int32_t imm = (int32_t)(imm12 | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1)); // Sign-extended immediate

    bool takeBranch = false;
    switch (funct3)
    {
    case 0x0: // BEQ
        takeBranch = (regfile[rs1] == regfile[rs2]);
        break;
    case 0x1: // BNE
        takeBranch = (regfile[rs1] != regfile[rs2]);
        break;
    case 0x4: // BLT
        takeBranch = ((int32_t)regfile[rs1] < (int32_t)regfile[rs2]);
        break;
    case 0x5: // BGE
        takeBranch = ((int32_t)regfile[rs1] >= (int32_t)regfile[rs2]);
        break;
    case 0x6: // BLTU
        takeBranch = (regfile[rs1] < regfile[rs2]);
        break;
    case 0x7: // BGEU
        takeBranch = (regfile[rs1] >= regfile[rs2]);
        break;
    default:
        break;
    }

    if (takeBranch)
    {
        jumpAddr = pc + imm;
        jumpEn = true;
    }
}
void RVX_Machine::RV32I_Type_U()
{
    uint8_t opcode = inst & 0x7F;
    uint8_t rd = (inst >> 7) & 0x1F;
    int32_t imm = (int32_t)(inst & 0xFFFFF000); // Upper 20 bits
    switch (opcode)
    {
    case OP_U:
        // LUI
        regfile[rd] = imm;
        break;
    case OP_UA:
        // AUIPC
        regfile[rd] = pc + imm;
        break;
    default:
        break;
    }
}
void RVX_Machine::RV32I_Type_J()
{
    uint8_t rd = (inst >> 7) & 0x1F;
    uint32_t imm10_1 = (inst >> 21) & 0x3FF;
    uint32_t imm11 = (inst >> 20) & 0x1;
    uint32_t imm19_12 = (inst >> 12) & 0xFF;
    int32_t imm20 = ((int32_t)inst >> 11) & 0xFFF00000;

    int32_t imm = (int32_t)(imm20 | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1)); // Sign-extended immediate

    // JAL
    regfile[rd] = pc + 4;
    jumpAddr = pc + imm;
    jumpEn = true;
}

#endif // _RVX_RV32I_CPP_