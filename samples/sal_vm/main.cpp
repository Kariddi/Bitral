#include <RecFunctions.h>
#include <iostream>
#include <Globals.h>
#include <BitralContext.h>

#define OPCODE_NUM 30

enum Opcodes { LD, ST, ADD, ADDI, SUB, SUBI, MUL, MULI, DIV, DIVI, CMP, CMPI,
               MOV, MOVI, OR, ORI, XOR, XORI, AND, ANDI, TEST, TESTI, BRE, BRLE,
               BRL, BRG, BRGE, BR, HLT, NOP };

RecompileFunction recompile_routines[OPCODE_NUM];

void initRoutines() {

  recompile_routines[ST] = &recST;
  recompile_routines[ADD] = &recADD;
  recompile_routines[ADDI] = &recADDI;
  recompile_routines[CMPI] = &recCMPI;
  recompile_routines[MOVI] = &recMOVI;
  recompile_routines[BRLE] = &recBRLE;
  recompile_routines[HLT] = &recHLT;

}

Registers Regs;

BitralRegisters BitralRegs;

int main() {
  initRoutines();
  Bitral::BitralContext b;
  BitralRegs.A = b.addRegister(32, "A", &Regs.A);

  std::cout << BitralRegs.A << std::endl;

  return 0;
}
