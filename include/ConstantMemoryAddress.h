#ifndef __BITRAL_CONSTANT_MEMORY_ADDRESS_H__
#define __BITRAL_CONSTANT_MEMORY_ADDRESS_H__

#include <llvm/LLVMContext.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <MemoryAddress.h>
#include <Immediate.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;

/**
  Are intended to be supported values larger of 64 bits somehow ... but this still hasn't been done
**/

class ConstantMemoryAddress : public MemoryAddress {

Immediate ImmediateValue;
  friend class BitralContext;

public:
  ConstantMemoryAddress(const Immediate& immediate) : ImmediateValue(immediate) {}
  
  // ConstantMemoryAddress(const BitralContext& Context, std::uint16_t bit_size, ArrayRef<std::uint64_t> address) : Address(bit_size, address) {}

  virtual std::uint16_t getBitSize();
};

}

#endif
