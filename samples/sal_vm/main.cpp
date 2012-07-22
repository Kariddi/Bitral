/*  Copyright (c) 2012 Marcello Maggioni 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
CONTRACT, TORT OR OTHERWISE, RISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.

*/


#include <RecFunctions.h>
#include <iostream>
#include <fstream>
#include <boost/unordered_map.hpp>
#include <RegisterCodes.h>
#include <Globals.h>
#include <BitralContext.h>

#define OPCODE_NUM 30
#define OPCODE ((opcode >> 24) & 0xff)

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

boost::uint32_t opcode;

Bitral::CodeRegion* Region;

boost::unordered_map<RegisterCodes, std::string> CodeNameMap; 

void initBitralData(Bitral::BitralContext &b) {

  BitralRegs.A = b.addRegister(32, "A", &Regs[REG_A]);
  CodeNameMap[REG_A] = "A";
  BitralRegs.B = b.addRegister(32, "B", &Regs[REG_B]);
  CodeNameMap[REG_B] = "B";
  BitralRegs.C = b.addRegister(32, "C", &Regs[REG_C]);
  CodeNameMap[REG_C] = "C";
  BitralRegs.D = b.addRegister(32, "D", &Regs[REG_D]);
  CodeNameMap[REG_D] = "D";
  BitralRegs.E = b.addRegister(32, "E", &Regs[REG_E]);
  CodeNameMap[REG_E] = "E";
  BitralRegs.F = b.addRegister(32, "F", &Regs[REG_F]);
  CodeNameMap[REG_F] = "F";
  BitralRegs.SP = b.addRegister(32, "SP", &Regs[REG_SP]);
  CodeNameMap[REG_SP] = "SP";
  BitralRegs.PC = b.addRegister(32, "PC", &Regs[REG_PC]);
  CodeNameMap[REG_PC] = "PC";
  BitralRegs.STATUS = b.addRegister(32, "STATUS", &Regs[REG_STATUS]);
  CodeNameMap[REG_STATUS] = "STATUS";
  b.setMemorySpace(Mem.mem8, sizeof(Mem));
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
