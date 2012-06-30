#include <BitralContext.h>

using namespace Bitral;

Register* BitralContext::addRegister(std::uint16_t bit_size, std::string name) {
  Register* NewRegister = new Register();
  Registers[name] = NewRegister;

  return NewRegister;
}

Register* BitralContext::addRegister(std::uint16_t bit_size, std::string name, void* memory_map_location) {
  Register* NewRegister = new Register();
  Registers[name] = NewRegister;

  return NewRegister;
}

Register* BitralContext::getRegister(std::string name) {
  RegisterMapIterator FoundRegister = Registers.find(name);
  if (FoundRegister != Registers.end())
    return FoundRegister->second;

  return NULL;
}

BitralContext::~BitralContext() {
  for (auto I = Registers.begin(), E = Registers.end(); I != E; ++I)
    delete I->second;
}
