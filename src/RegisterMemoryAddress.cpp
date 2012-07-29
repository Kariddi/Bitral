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


#include <algorithm>
#include <BitralContext.h>
#include <Register.h>
#include <Immediate.h>
#include <RegisterMemoryAddress.h>
using namespace Bitral;

RegisterMemoryAddress::RegisterMemoryAddress(BitralContext& context, Register* base_reg) :
                                             MemoryAddress(computeBS(base_reg, NULL, 
                                             Immediate(context,0,0), Immediate(context,0,0))), 
                                             Base(base_reg), Index(NULL), 
                                             Scale(Immediate(context,0,0)),
                                             Displacement(Immediate(context,0,0)) {}

RegisterMemoryAddress::RegisterMemoryAddress(BitralContext& context, Register* base_reg, 
                                             Register* index, const Immediate& scale) :
                                             MemoryAddress(computeBS(base_reg, NULL, 
                                             scale, Immediate(context,0,0))), 
                                             Base(base_reg), Index(index),
                                             Scale(scale), Displacement(Immediate(context,0,0)) {}

RegisterMemoryAddress::RegisterMemoryAddress(BitralContext& context, Register* base_reg, Register* index, 
                                             const Immediate& scale, 
                                             const Immediate& displacement) :
                                             MemoryAddress(computeBS(base_reg, index, scale, displacement)),
                                             Base(base_reg), Index(index), Scale(scale),
                                             Displacement(displacement) {}

RegisterMemoryAddress::RegisterMemoryAddress(BitralContext& context, Register* base_reg, 
                                             const Immediate& displacement) : 
                                             MemoryAddress(computeBS(base_reg, NULL, 
                                             Immediate(context,0,0), displacement)), 
                                             Base(base_reg), Index(NULL), 
                                             Scale(Immediate(context,0,0)),
                                             Displacement(displacement) {}

llvm::Value* RegisterMemoryAddress::getValue(llvm::IRBuilder<>& builder) const {

  if (Index != NULL) {
    llvm::Value* ToReturn = NULL;
    llvm::Value* ScaleIdxVal = builder.CreateMul(Scale.getValue(builder), Index->getValue(builder)); 
    ToReturn = builder.CreateAdd(Base->getValue(builder), ScaleIdxVal); 
    return builder.CreateAdd(ToReturn, Displacement.getValue(builder));
  }
  
  return builder.CreateAdd(Base->getValue(builder), Displacement.getValue(builder));
}

boost::uint16_t RegisterMemoryAddress::computeBS(const Register* Base, const Register* Index, 
                                                  const Immediate& Scale, const Immediate& Displacement) {
    if (Index != NULL) {
      return std::max(Base->getBitSize(), std::max(Index->getBitSize(), 
                      std::max(Scale.getBitSize(), Displacement.getBitSize())));
    }
    
    return std::max(Base->getBitSize(), std::max(Scale.getBitSize(), Displacement.getBitSize())); 
}

