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


#ifndef __BITRAL_OPERAND_H__
#define __BITRAL_OPERAND_H__
#include <llvm/Value.h>
#include <llvm/IRBuilder.h>
#include <BitralConfig.h>

namespace Bitral {

class Operand {
protected:
  boost::uint16_t BitSize;

  Operand(boost::uint16_t bit_size) : BitSize(bit_size) {}
public:
  boost::uint16_t getBitSize() const { return BitSize; }
  /** Returns the value representing the Operand. If the Operand is memory stored
      it will be loaded from the memory, (through code added to the IRBuilder), otherwise
      it should return the object representing the initial value of the operand
  **/ 
  virtual llvm::Value* getValue(llvm::IRBuilder<>& builder) const = 0;
  /** Sets the value for the Operand. If the operand is memory stored it will be stored to memory.
      It returns false if the operand doesn't support value storing
  **/
  virtual bool setValue(llvm::IRBuilder<>& builder, llvm::Value* val) = 0;
  virtual ~Operand() { }
};

}

#endif
