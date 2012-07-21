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
