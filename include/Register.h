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


#ifndef __BITRAL_REGISTER_H__
#define __BITRAL_REGISTER_H__

#include <string>
#include <llvm/Support/IRBuilder.h>
#include <MemoryStoredOperand.h>
#include <BitralConfig.h>
#include <llvm/GlobalVariable.h>

namespace llvm {
class Value;
}

namespace Bitral {

class RegisterMemoryAddress;
class BitralContext;
class CodeRegion;
class CompilerState;

class Register : public MemoryStoredOperand {
  //friend class RegisterMemoryAddress;
  friend class BitralContext;

public:
  struct Interval {
    boost::uint16_t Begin;
    boost::uint16_t End;
    Interval() : Begin(0), End(0) {}
    Interval(boost::uint16_t begin, boost::uint16_t end) : Begin(begin), End(end) {}
  };

private:
  Register* BaseReg;
  Interval Part;
  llvm::GlobalVariable* InitGV(CompilerState& c_state, void* address, boost::uint16_t bit_size);
  Register(CompilerState& c_state, void* address, boost::uint16_t bit_size) : 
                              MemoryStoredOperand(bit_size, InitGV(c_state, address, bit_size)), 
                              BaseReg(NULL) {} 
  Register(Register* base_reg, Interval ival) : MemoryStoredOperand(ival.End-ival.Begin, base_reg->RegGV), 
                                                BaseReg(base_reg), Part(ival) {} 
  Register(const Register& to_copy) : MemoryStoredOperand(*this), BaseReg(to_copy.BaseReg), 
                                      Part(to_copy.Part)  {}
};

}

#endif
