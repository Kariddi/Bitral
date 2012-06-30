#include <BitralContext.h>
#include <Register.h>
#include <cassert>
#undef NDEBUG

using namespace Bitral;

int main() {

  BitralContext b;

  Register* Reg = b.addRegister(32, "eax");

  Register* Find = b.getRegister("eax");

  assert(Reg == Find);

  return 0;

}
