#ifndef __BITRAL_CONSTANT_MEMORY_ADDRESS_H__
#define __BITRAL_CONSTANT_MEMORY_ADDRESS_H__

#include <MemoryAddress.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;

/**
  Are intended to be supported values larger of 64 bits somehow ... but this still hasn't been done
**/

class ConstantMemoryAddress : public MemoryAddress {

  std::uint64_t Address;
  friend class BitralContext;

protected:
  ConstantMemoryAddress(BitralContext& Context, std::uint16_t bit_size, std::uint64_t address);

  // ConstantMemoryAddress(const BitralContext& Context, std::uint16_t bit_size, ArrayRef<std::uint64_t> address) : Address(bit_size, address) {}
 
};

}

#endif
