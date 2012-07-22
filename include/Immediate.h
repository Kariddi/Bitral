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


#ifndef __BITRAL_IMMEDIATE_H__
#define __BITRAL_IMMEDIATE_H__

#include <Operand.h>
#include <functional>
#include <boost/functional/hash.hpp>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;

class Immediate : public Operand {

//  friend class BitralContext;
  friend class boost::hash<Immediate>;
public:
  Immediate(BitralContext& context, boost::uint16_t bit_size, boost::uint64_t value); 
  bool operator==(const Immediate& imm) const { 
    llvm::ConstantInt* ConstVal1 = llvm::dyn_cast<llvm::ConstantInt>(OperandValue);
    llvm::ConstantInt* ConstVal2 = llvm::dyn_cast<llvm::ConstantInt>(imm.OperandValue);
    return ConstVal1->getValue() == ConstVal2->getValue();
  }
  Immediate& operator+=(boost::uint32_t val) {
    OperandValue = llvm::ConstantInt::get(OperandValue->getType(), 
                                          (llvm::dyn_cast<llvm::ConstantInt>(OperandValue)->getValue() +
                                           val));
    return *this;
  }
};

}

namespace boost {
template<>
class boost::hash<Bitral::Immediate> : public std::unary_function<Bitral::Immediate, std::size_t> {
public:
  std::size_t operator()(const Bitral::Immediate& imm) const {
    const llvm::APInt& ap_int = llvm::dyn_cast<llvm::ConstantInt>(imm.OperandValue)->getValue();
    const boost::uint64_t* raw = reinterpret_cast<const boost::uint64_t*>(ap_int.getRawData());
    boost::uint64_t sum = raw[0];
    int word_num = ap_int.getNumWords();
    for (int i = 1; i < word_num; ++i)
      sum += raw[i];
    return boost::hash<boost::uint64_t>()(sum);
  }
};
}

#endif
