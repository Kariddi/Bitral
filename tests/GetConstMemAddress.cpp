#include <BitralContext.h>
#include <ConstantMemoryAddress.h>
#include <cassert>
#undef NDEBUG

using namespace Bitral;

int main() {

  BitralContext b;

  ConstantMemoryAddress MemAddr = b.getConstantMemoryAddress(32, 1000);

  assert(MemAddr.getBitSize() == 32);

  return 0;

}
