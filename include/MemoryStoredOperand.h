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


#ifndef __BITRAL_MEMORY_STORED_OPERAND_H__
#define __BITRAL_MEMORY_STORED_OPERAND_H__

#include <llvm/GlobalVariable.h>
#include <llvm/IRBuilder.h>
#include <DestinationOperand.h>

namespace Bitral {

class MemoryStoredOperand : public DestinationOperand {

protected:
  llvm::GlobalVariable* RegGV;
  MemoryStoredOperand(boost::uint16_t bit_size, llvm::GlobalVariable* op_value) : DestinationOperand(bit_size), RegGV(op_value) {}
public:
  virtual llvm::Value* getValue(llvm::IRBuilder<>& builder) const { 
    return builder.CreateLoad(RegGV);
  }
  
  virtual bool setValue(llvm::IRBuilder<>& builder, llvm::Value* val) { 
    builder.CreateStore(val, RegGV);
    return true;
  }

};

}

#endif
