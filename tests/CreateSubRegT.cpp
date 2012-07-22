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
#include <Register.h>
#include <cassert>
#undef NDEBUG

using namespace Bitral;

enum RegCodes { EAX, EBX, ECX};

int main() {

  BitralContext b;

  Register* Reg = b.addRegister(32, "EBX", NULL);
  Register* SubReg = b.addSubRegister(Reg, Register::Interval(0,15), "BX");

  Register* Find = b.getRegister("EBX");
  Register* SubFind = b.getRegister("BX");

  assert(Reg == Find);
  assert(SubReg == SubFind);

  return 0;

}
