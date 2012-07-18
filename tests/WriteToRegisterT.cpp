#include <BitralContext.h>
#include <iostream>
#include <RegisterMemoryAddress.h>
#include <CodeRegion.h>
#include <cassert>
#undef NDEBUG
//#define DEBUG

using namespace Bitral;

boost::uint32_t reg_var = 100;
boost::uint8_t mem[100];

int main() {

  BitralContext b;

  Register* reg = b.addRegister(32, "A", &reg_var);
  b.setMemorySpace(mem, sizeof(mem));
  CodeRegion* Region = b.createNewCodeRegion(0);
  Region->increaseMemoryPosition(4);
  Region->createXOR(reg, reg);
  Region->closeRegion();

  CodeRegion::CodePointer Code = Region->compile(); 
  assert(reg_var == 100);
  Code();
  std::cout << reg_var << std::endl;
  assert(reg_var == 0);

  return 0;

}
