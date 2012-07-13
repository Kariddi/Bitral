#include <BitralContext.h>
#include <iostream>
#include <RegisterMemoryAddress.h>
#include <cassert>
#undef NDEBUG
//#define DEBUG

using namespace Bitral;

int main() {

  BitralContext b;

  Register* reg = b.addRegister(32, "A");
  Register* index = b.addRegister(16, "B");
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
