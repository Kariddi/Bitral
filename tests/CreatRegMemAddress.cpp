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


#include <BitralContext.h>
#include <iostream>
#include <RegisterMemoryAddress.h>
#include <cassert>
#undef NDEBUG
//#define DEBUG

using namespace Bitral;

int main() {

  BitralContext b;

  Register* reg = b.addRegister(32, "A", NULL);
  Register* index = b.addRegister(16, "B", NULL);
  assert(reg->getID() != index->getID());
  RegisterMemoryAddress RegAddr(b,reg);
  assert(RegAddr.getBitSize() == 32);
  RegAddr = RegisterMemoryAddress(b,reg, index, Immediate(b,16, 4), Immediate(b,32, 1000));
  assert(RegAddr.getBitSize() == 32);
  RegAddr = RegisterMemoryAddress(b,reg, index, Immediate(b,80, 4));
  assert(RegAddr.getBitSize() == 80);
  RegAddr = RegisterMemoryAddress(b,reg, Immediate(b,64, 1000));
  assert(RegAddr.getBitSize() == 64);

  return 0;

}
