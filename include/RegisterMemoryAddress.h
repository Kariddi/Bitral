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


#ifndef __BITRAL_REGISTER_MEMORY_ADDRESS_H__
#define __BITRAL_REGISTER_MEMORY_ADDRESS_H__


namespace Bitral {

class Register;

class RegisterMemoryAddress : public MemoryAddress {

  Register* Base;
  Register* Index;
  Immediate Scale;
  Immediate Displacement;
  //friend class BitralContext;

public:
  RegisterMemoryAddress(BitralContext& context, Register* base_reg);

  RegisterMemoryAddress(BitralContext& context, Register* base_reg, Register* index, const Immediate& scale);
  RegisterMemoryAddress(BitralContext& context, Register* base_reg, Register* index, 
                        const Immediate& scale, const Immediate& displacement);
  RegisterMemoryAddress(BitralContext& context, Register* base_reg, const Immediate& displacement);

  virtual boost::uint16_t getBitSize();
};

}

#endif
