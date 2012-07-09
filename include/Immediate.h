#ifndef __BITRAL_IMMEDIATE_H__
#define __BITRAL_IMMEDIATE_H__

#include <llvm/LLVMContext.h>
#include <Operand.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;

class Immediate : public Operand {

  friend class BitralContext;
public:
  Immediate(llvm::LLVMContext& context, std::uint16_t bit_size, std::uint64_t value) : Operand(bit_size, 
                                                                     llvm::ConstantInt::get(
                                                                     llvm::IntegerType::get(context, 
                                                                     bit_size), value)) {}
};

}

#endif
