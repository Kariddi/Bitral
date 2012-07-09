#include <BitralContext.h>
#include <Register.h>
#include <cassert>
#undef NDEBUG

using namespace Bitral;

enum RegCodes { EAX, EBX, ECX};

int main() {

  BitralContext b;

  Register* Reg = b.addRegister(32, EBX);

  Register* Find = b.getRegister(EBX);

  assert(Reg == Find);

  return 0;

}
