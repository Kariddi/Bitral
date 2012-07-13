#include <RecFunctions.h>
#include <iostream>
#include <fstream>
#include <RegisterCodes.h>
#include <Globals.h>
#include <BitralContext.h>

#define OPCODE_NUM 30
#define OPCODE (opcode >> 24) & 0xff

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

Register Regs[REG_NUM];

BitralRegisters BitralRegs;

Memory Mem;

Bitral::BitralContext BContext;

uint32_t opcode;

Bitral::CodeRegion* Region;

void initBitralData(Bitral::BitralContext &b) {

  BitralRegs.A = b.addRegister(32, "A", &Regs[REG_A]);
  BitralRegs.B = b.addRegister(32, "B", &Regs[REG_B]);
  BitralRegs.C = b.addRegister(32, "C", &Regs[REG_C]);
  BitralRegs.D = b.addRegister(32, "D", &Regs[REG_D]);
  BitralRegs.E = b.addRegister(32, "E", &Regs[REG_E]);
  BitralRegs.F = b.addRegister(32, "F", &Regs[REG_F]);
  BitralRegs.SP = b.addRegister(32, "SP", &Regs[REG_SP]);
  BitralRegs.PC = b.addRegister(32, "PC", &Regs[REG_PC]);
  BitralRegs.STATUS = b.addRegister(32, "STATUS", &Regs[REG_STATUS]);
  b.setMemorySpace(Mem.mem8);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "ERROR: Not enough arguments to command-line" << std::endl;
    return 1;
  }
  initRoutines();
  initBitralData(BContext);
  
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

  Region = BContext.createNewCodeRegion(current_mem_ptr);

  Regs[REG_PC] = current_mem_ptr;
  opcode = *(Mem.mem32 + current_mem_ptr);
  while (OPCODE != HLT) {
//    while (OPCODE < BRE || OPCODE == NOT) {
      recompile_routines[OPCODE]();
      opcode = *(Mem.mem32+current_mem_ptr++);
//    }
  }

  Region->closeRegion();
  void(*Code)() = Region->compile();
  Code();

  return 0;
}
