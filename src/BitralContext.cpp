#include <BitralContext.h>

using namespace Bitral;

Register* BitralContext::addRegister(std::uint16_t bit_size, std::uint32_t code) {
  Register* NewRegister = new Register();
  Registers[code] = NewRegister;

  return NewRegister;
}

Register* BitralContext::addRegister(std::uint16_t bit_size, std::uint32_t code, const void* memory_map_location) {
  Register* NewRegister = new Register();
  Registers[code] = NewRegister;

  return NewRegister;
}

Register* BitralContext::getRegister(std::uint32_t code) const {
  RegisterMapConstIterator FoundRegister = Registers.find(code);
  if (FoundRegister != Registers.end())
    return FoundRegister->second;

  return NULL;
}

ConstantMemoryAddress BitralContext::getConstantMemoryAddress(std::uint16_t bit_size, 
                                                              std::uint64_t address) {
  return ConstantMemoryAddress(*this, bit_size, address); 
}
 
BitralContext::~BitralContext() {
  for (auto I = Registers.begin(), E = Registers.end(); I != E; ++I)
    delete I->second;
}
