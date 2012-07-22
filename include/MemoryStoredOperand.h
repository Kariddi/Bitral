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
#include <llvm/Support/IRBuilder.h>
#include <DestinationOperand.h>

namespace Bitral {

class MemoryStoredOperand : public DestinationOperand {

protected:
  llvm::GlobalVariable* RegGV;
public:
  virtual bool isMemoryStored() { return true; }
  virtual void generateLoadingCode(llvm::IRBuilder<>& builder) = 0;
  virtual void generateStoringCode(llvm::IRBuilder<>& builder) const = 0;
  MemoryStoredOperand(boost::uint16_t bit_size, llvm::GlobalVariable* op_value) : DestinationOperand(bit_size, op_value), RegGV(op_value) {}

};

}

#endif
