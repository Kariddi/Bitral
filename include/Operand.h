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
#include <BitralConfig.h>

namespace Bitral {

class Operand {
public:
  typedef boost::uint32_t IdType;
private:
  static IdType NextId;

protected:
  boost::uint16_t BitSize;
  llvm::Value* OperandValue;
  boost::uint32_t UniqueID;

  Operand(boost::uint16_t bit_size, llvm::Value* op_value) : BitSize(bit_size), OperandValue(op_value) {
    UniqueID = NextId++;
  }
public:
  boost::uint16_t getBitSize() const { return BitSize; }
  llvm::Value* getValue() const { return OperandValue; }
  IdType getID() const { return UniqueID; }
  virtual ~Operand() { }
  //virtual void add(Operand* addend) = 0;
  //virtual Comparison* compare(Operand* op) = 0;
  //virtual void subtract(Operand* addend) = 0;
};

}

#endif
