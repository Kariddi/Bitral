#ifndef __BITRAL_DESTINATION_OPERAND_H__
#define __BITRAL_DESTINATION_OPERAND_H__

#include <Operand.h>
#include <BitralConfig.h>

namespace llvm {
  class Value;
}

namespace Bitral {

class DestinationOperand : public Operand {
//  friend struct Hasher;
//  std::string Name;
protected:
  DestinationOperand(boost::uint16_t bit_size, llvm::Value* op_value) : Operand(bit_size, op_value) {}
//  DestinationOperand(std::uint16_t bit_size, llvm::Value* op_value) : Operand(bit_size, op_value) {}
public:
/*  struct Hasher {
    size_t operator()(const DestinationOperand& X) {
      return std::hash<std::string>()(X.Name);
    }
  };*/
  void setValue(llvm::Value* val) { OperandValue = val; }
//  virtual void setValue(CodeRegion* region, llvm::Value* val) = 0;
  virtual bool isMemoryStored() = 0;
  virtual DestinationOperand* clone() = 0;
};

}

#endif
