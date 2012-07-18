#ifndef __BITRAL_MEMORY_ADDRESS_H__
#define __BITRAL_MEMORY_ADDRESS_H__

#include <Operand.h>
#include <BitralConfig.h>

namespace Bitral {

class MemoryAddress {
protected:
  //MemoryAddress(std::uint16_t bit_size, llvm::Value* op_value) : Operand(bit_size, op_value) {}

  virtual boost::uint16_t getBitSize() = 0;
public:
  virtual ~MemoryAddress() {}
};

}

#endif
