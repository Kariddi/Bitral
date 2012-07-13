#include <BitralContext.h>

using namespace Bitral;

Register* BitralContext::addRegister(std::uint16_t bit_size, const std::string& name) {
  Register* NewRegister = new Register(bit_size);
  Registers[name] = NewRegister;

  return NewRegister;
}

Register* BitralContext::addRegister(std::uint16_t bit_size, const std::string& name, const void* memory_map_location) {
  Register* NewRegister = new Register(bit_size);
  Registers[name] = NewRegister;

  return NewRegister;
}

Register* BitralContext::getRegister(const std::string& name) const {
  RegisterMapConstIterator FoundRegister = Registers.find(name);
  if (FoundRegister != Registers.end())
    return FoundRegister->second;

  return NULL;
}

//ConstantMemoryAddress BitralContext::getConstantMemoryAddress(std::uint16_t bit_size, 
//                                                              std::uint64_t address) {
/*ConstantMemoryAddress BitralContext::getConstantMemoryAddress(const Immediate& immediate) {
  return ConstantMemoryAddress(immediate); 
}*/
 
BitralContext::~BitralContext() {
  for (auto I = Registers.begin(), E = Registers.end(); I != E; ++I)
    delete I->second;
}
