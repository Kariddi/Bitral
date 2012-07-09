#ifndef __BITRAL_OPERAND_H__
#define __BITRAL_OPERAND_H__
#include <llvm/Value.h>
#include <BitralConfig.h>

namespace Bitral {

class Operand {
protected:
  std::uint16_t BitSize;
  llvm::Value* OperandValue;

public:
  std::uint16_t getBitSize() { return BitSize; }
  Operand(std::uint16_t bit_size, llvm::Value* op_value) : BitSize(bit_size), OperandValue(op_value) {}
  //virtual void add(Operand* addend) = 0;
  //virtual Comparison* compare(Operand* op) = 0;
  //virtual void subtract(Operand* addend) = 0;
};

}

#endif
