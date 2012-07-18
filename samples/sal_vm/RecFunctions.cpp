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

  boost::uint8_t origin_reg = REG_1;
  boost::uint8_t address_reg = REG_2;
  
  Bitral::Register* o_reg = BContext.getRegister(*CodeNameMap.find(origin_reg));
  Bitral::RegisterMemoryAddress a_reg(address_reg);

  Region->createStore(o_reg, a_reg);
  Region->increaseMemoryPosition(4);
  //BContext.getMemory()

}

void recADD() {
  boost::uint8_t reg_1 = REG_1;
  boost::uint8_t reg_2 = REG_2;
  
  Bitral::Register* reg = BContext.getRegister(*CodeNameMap.find(reg_1));
  Bitral::Register* reg2 = BContext.getRegister(*CodeNameMap.find(reg_2));

  Region->createAdd(reg, reg2, reg);
  Region->increaseMemoryPosition(4);
}

void recADDI() {
  Bitral::Register* reg = BContext.getRegister(*CodeNameMap.find(REG_ONLY));

  Region->createAdd(reg, reg, Bitral::Immediate(BContext, 16, IMMEDIATE));
  Region->increaseMemoryPosition(4);
}

void recCMPI() {
  Bitral::Register* reg = BContext.getRegister(*CodeNameMap.find(REG_ONLY));
  Bitral::Register* status = BContext.getRegister(*CodeNameMap.find(REG_STATUS));

  Bitral::CompareRes cmp_res(Region->createCompare(reg, Bitral::Immediate(BContext, 16, IMMEDIATE));
  Region->createConditionalOr(cmp_res, CompareRes::LESS, status, Bitral::Immediate(BContext, 32, 1), Bitral::Immediate(BContext, 32, 0));
  Region->createConditionalOr(cmp_res, CompareRes::EQUAL, status, Bitral::Immediate(BContext, 32, 2), Bitral::Immediate(BContext, 32, 0));
  Region->increaseMemoryPosition(4);
}

void recMOVI() {
  Bitral::Register* reg = BContext.getRegister(*CodeNameMap.find(REG_ONLY));

  Region->createMov(reg, Bitral::Immediate(BContext, 16, IMMEDIATE));
  Region->increaseMemoryPosition(4);
}

void recBRLE() {
  Bitral::Register* status = BContext.getRegister(*CodeNameMap.find(REG_STATUS));
  Bitral::Temporary temp(BContext, 16, 0);
  Region->createOr(&temp, status, Bitral::Immediate(BContext, 32, 3));
  Bitral::CompareRes cmp_res(Region->createMoreThanCompare(&temp, Bitral::Immediate(BContext, 32, 0)));
  Region->createConditionalBranch(cmp_res, Bitral::Immediate(BContext, 16, IMMEDIATE));
  Region->increaseMemoryPosition(4);
}

void recHLT() {

  Region->increaseMemoryPosition(4);

}

