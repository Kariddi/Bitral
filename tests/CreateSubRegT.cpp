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
