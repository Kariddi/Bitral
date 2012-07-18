#ifndef __SALVM_GLOBALS_H__
#define __SALVM_GLOBALS_H__
//#include <cstdint>
#include <BitralContext.h>

#define _1kb 1024
#define REG_NUM 9

typedef union {
  boost::uint8_t mem8[_1kb];
  boost::uint16_t mem16[_1kb/2];
  boost::uint32_t mem32[_1kb/4];
} Memory;

typedef boost::uint32_t Register;

/*typedef struct Registers {
  Register A;
  Register B;
  Register C;
  Register D;
  Register E;
  Register F;
  Register SP;
  Register PC;
  Register STATUS;
} Registers;
*/

typedef struct BitralRegisters {
  Bitral::Register* A;
  Bitral::Register* B;
  Bitral::Register* C;
  Bitral::Register* D;
  Bitral::Register* E;
  Bitral::Register* F;
  Bitral::Register* SP;
  Bitral::Register* PC;
  Bitral::Register* STATUS;
} BitralRegisters;

typedef void(*RecompileFunction)();

enum Opcodes { LD, ST, ADD, ADDI, SUB, SUBI, MUL, MULI, DIV, DIVI, CMP, CMPI,
               MOV, MOVI, OR, ORI, XOR, XORI, AND, ANDI, TEST, TESTI, BRE, BRLE,
               BRL, BRG, BRGE, BR, HLT, NOP };

#endif
