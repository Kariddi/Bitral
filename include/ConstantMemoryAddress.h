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
  
  ConstantMemoryAddress operator+(boost::uint32_t val) {
    return ConstantMemoryAddress(ImmediateValue + val);
  }

};

}

namespace boost {
template<>
class hash<Bitral::ConstantMemoryAddress> :
                           public std::unary_function<Bitral::ConstantMemoryAddress, std::size_t> {
public:
  std::size_t operator()(const Bitral::ConstantMemoryAddress& cma) const {
    return hash<Bitral::Immediate>()(cma.ImmediateValue);
  }
};
}


#endif
