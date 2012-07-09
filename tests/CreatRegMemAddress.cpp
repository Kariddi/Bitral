#include <BitralContext.h>
#include <iostream>
#include <RegisterMemoryAddress.h>
#include <cassert>
#undef NDEBUG
//#define DEBUG

using namespace Bitral;

int main() {

  BitralContext b;

  Register* reg = b.addRegister(32, 0);
  Register* index = b.addRegister(16, 1);
  RegisterMemoryAddress RegAddr = b.getRegisterMemoryAddress(reg);
  assert(RegAddr.getBitSize() == 32);
  RegAddr = b.getRegisterMemoryAddress(reg, index, b.getImmediate(16, 4), b.getImmediate(32, 1000));
  assert(RegAddr.getBitSize() == 32);
  RegAddr = b.getRegisterMemoryAddress(reg, index, b.getImmediate(80, 4));
  assert(RegAddr.getBitSize() == 80);
  RegAddr = b.getRegisterMemoryAddress(reg, b.getImmediate(64, 1000));
  assert(RegAddr.getBitSize() == 64);

  return 0;

}
