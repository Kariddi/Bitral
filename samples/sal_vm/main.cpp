#include <RecFunctions.h>
#include <iostream>
#include <fstream>
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

Memory Mem;

void initBitralData(Bitral::BitralContext &b) {

  BitralRegs.A = b.addRegister(32, "A", &Regs.A);
  BitralRegs.B = b.addRegister(32, "B", &Regs.B);
  BitralRegs.C = b.addRegister(32, "C", &Regs.C);
  BitralRegs.D = b.addRegister(32, "D", &Regs.D);
  BitralRegs.E = b.addRegister(32, "E", &Regs.E);
  BitralRegs.F = b.addRegister(32, "F", &Regs.F);
  BitralRegs.SP = b.addRegister(32, "SP", &Regs.SP);
  BitralRegs.PC = b.addRegister(32, "PC", &Regs.PC);
  BitralRegs.STATUS = b.addRegister(32, "STATUS", &Regs.STATUS);

}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "ERROR: Not enough arguments to command-line" << std::endl;
    return 1;
  }
  initRoutines();
  Bitral::BitralContext b;
  initBitralData(b);
  
  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "ERROR: Can't open the file " << std::string(argv[1]) << std::endl;
    return 1;
  }
  
  int next_byte, current_mem_ptr = 0;
  while ((next_byte = input.get()) == 0)
    input.read((char*)Mem.mem32 + (current_mem_ptr++), sizeof(*Mem.mem32));

  input.unget();
  std::streampos curr_pos = input.tellg();
  input.seekg(0, std::ios_base::end);
  std::streampos remaining_size = input.tellg() - curr_pos;
  input.seekg(curr_pos, std::ios_base::beg);
  input.read((char*)Mem.mem32 + current_mem_ptr, remaining_size);

  return 0;
}
