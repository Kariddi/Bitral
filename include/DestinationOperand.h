#ifndef __BITRAL_DESTINATION_OPERAND_H__
#define __BITRAL_DESTINATION_OPERAND_H__

#include <Operand.h>
#include <BitralConfig.h>

namespace llvm {
  class Value;
}

namespace Bitral {

class DestinationOperand : public Operand {

protected:
  DestinationOperand(std::uint16_t bit_size, llvm::Value* op_value) : Operand(bit_size, op_value) {}

};

}

#endif
