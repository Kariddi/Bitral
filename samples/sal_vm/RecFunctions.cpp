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
  Bitral::Register* reg = BContext.getRegister(REG_ONLY);

  Region->createAdd(reg, reg, &Bitral::Immediate(BContext, 16, IMMEDIATE));
}

void recCMPI() {
  Bitral::Register* reg = BContext.getRegister(REG_ONLY);
  Bitral::Register* status = BContext.getRegister(REG_STATUS);

  Bitral::CompareRes cmp_res(Region->createCompare(reg, &Bitral::Immediate(BContext, 16, IMMEDIATE));
  Region->createConditionalOr(cmp_res, CompareRes::LESS, status, &Bitral::Immediate(BContext, 32, 1), &Bitral::Immediate(BContext, 32, 0));
  Region->createConditionalOr(cmp_res, CompareRes::EQUAL, status, &Bitral::Immediate(BContext, 32, 2), &Bitral::Immediate(BContext, 32, 0));
}

void recMOVI() {
  Bitral::Register* reg = BContext.getRegister(REG_ONLY);

  Region->createMov(reg, &Bitral::Immediate(BContext, 16, IMMEDIATE));

}

void recBRLE() {
  Bitral::Register* status = BContext.getRegister(REG_STATUS);
  Bitral::Temporary temp(BContext, 16, 0);
  Region->createOr(&temp, status, &Bitral::Immediate(BContext, 32, 3));
  Bitral::CompareRes cmp_res(Region->createMoreThanCompare(&temp, &Bitral::Immediate(BContext, 32, 0)));
  Region->createConditionalBranch(cmp_res, &Bitral::Immediate(BContext, 16, IMMEDIATE));
}

void recHLT() {

}

