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
  DestinationOperand* reg_cloned = reg->clone();
  assert(reg->getID() == reg_cloned->getID());

  delete reg_cloned;

  return 0;

}
