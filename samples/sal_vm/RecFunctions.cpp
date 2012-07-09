#include <RecFunctions.h>
#include <Globals.h>

#define REG_ONLY ((opcode >> 8) & 0xff)
#define REG_1 ((opcode >> 16) & 0xff)
#define REG_2 ((opcode >> 24) & 0xff)
#define IMMEDIATE ((opcode >> 16) & 0xffff)
#define OPCODE (opcode & 0xff)

extern uint32_t opcode;
extern Bitral::BitralContext BContext; 

void recST() {

  std::uint8_t origin_reg = REG_1;
  std::uint8_t address_reg = REG_2;
  
  Bitral::Register* o_reg = BContext.getRegister(origin_reg);
  Bitral::Register* a_reg = BContext.getMemoryOperand(a_reg);

  Region->createStore(o_reg, a_reg);
  //BContext.getMemory()

}

void recADD() {
  std::uint8_t reg_1 = REG_1;
  std::uint8_t reg_2 = REG_2;
  
  Bitral::Register* reg = BContext.getRegister(reg_1);
  Bitral::Register* reg2 = BContext.getRegister(reg_2);

  Region->createAdd(reg, reg2, reg);
}

void recADDI() {
}

void recCMPI() {

}

void recMOVI() {

}

void recBRLE() {

}

void recHLT() {

}

