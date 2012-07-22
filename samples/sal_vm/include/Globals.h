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
