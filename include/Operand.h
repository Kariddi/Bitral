#ifndef __BITRAL_OPERAND_H__
#define __BITRAL_OPERAND_H__
#include <llvm/Value.h>
#include <BitralConfig.h>

namespace Bitral {

class Operand {
public:
  typedef boost::uint32_t IdType;
private:
  static IdType NextId;

protected:
  boost::uint16_t BitSize;
  llvm::Value* OperandValue;
  boost::uint32_t UniqueID;

  Operand(boost::uint16_t bit_size, llvm::Value* op_value) : BitSize(bit_size), OperandValue(op_value) {
    UniqueID = NextId++;
  }
public:
  boost::uint16_t getBitSize() const { return BitSize; }
  llvm::Value* getValue() const { return OperandValue; }
  IdType getID() const { return UniqueID; }
  virtual ~Operand() { }
  //virtual void add(Operand* addend) = 0;
  //virtual Comparison* compare(Operand* op) = 0;
  //virtual void subtract(Operand* addend) = 0;
};

}

#endif
