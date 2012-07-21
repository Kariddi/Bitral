#ifndef __BITRAL_CONSTANT_MEMORY_ADDRESS_H__
#define __BITRAL_CONSTANT_MEMORY_ADDRESS_H__

#include <llvm/LLVMContext.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <MemoryAddress.h>
#include <Immediate.h>
#include <boost/functional/hash.hpp>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;

/**
  Are intended to be supported values larger of 64 bits somehow ... but this still hasn't been done
**/

class ConstantMemoryAddress : public MemoryAddress {

Immediate ImmediateValue;
  friend class BitralContext;
  friend class boost::hash<ConstantMemoryAddress>;
public:
  ConstantMemoryAddress(const Immediate& immediate) : ImmediateValue(immediate) {}
  //ConstantMemoryAddress() {} 
  // ConstantMemoryAddress(const BitralContext& Context, std::uint16_t bit_size, ArrayRef<std::uint64_t> address) : Address(bit_size, address) {}

  virtual boost::uint16_t getBitSize();
  bool operator==(const ConstantMemoryAddress& cma) const {
    return ImmediateValue == cma.ImmediateValue;
  }
  ConstantMemoryAddress& operator+=(boost::uint32_t val) {
    (ImmediateValue += val);
    return *this;
  }
};

}

namespace boost {
template<>
class boost::hash<Bitral::ConstantMemoryAddress> :
                           public std::unary_function<Bitral::ConstantMemoryAddress, std::size_t> {
public:
  std::size_t operator()(const Bitral::ConstantMemoryAddress& cma) const {
    return boost::hash<Bitral::Immediate>()(cma.ImmediateValue);
  }
};
}


#endif
