/*  Copyright (c) 2012 Marcello Maggioni 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
CONTRACT, TORT OR OTHERWISE, RISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.

*/


#include <CodeRegion.h>
#include <BitralContext.h>

using namespace Bitral;

CodeRegion* BitralContext::createNewCodeRegion(ConstantMemoryAddress starting_address) {
  CodeRegionMapIterator MapIt = CodeRegions.find(starting_address);
  if (CodeRegions.find(starting_address) != CodeRegions.end())
    return MapIt->second;
  CodeRegion* NewCodeRegion = new CodeRegion(CompState, starting_address);
  CodeRegions[starting_address] = NewCodeRegion;

  return NewCodeRegion;
}

void BitralContext::setMemorySpace(void* memory, boost::uint64_t size) {


}

llvm::GlobalValue* BitralContext::getMemorySpace() {

  return NULL;

}

/*
Register* BitralContext::addRegister(boost::uint16_t bit_size, const std::string& name) {
  Register* NewRegister = new Register(bit_size);
  Registers[name] = NewRegister;

  return NewRegister;
}*/

Register* BitralContext::addRegister(boost::uint16_t bit_size, const std::string& name, void* memory_map_location) {
  Register* NewRegister = new Register(CompState, memory_map_location, bit_size);
  Registers[name] = NewRegister;

  return NewRegister;
}

Register* BitralContext::getRegister(const std::string& name) const {
  RegisterMapConstIterator FoundRegister = Registers.find(name);
  if (FoundRegister != Registers.end())
    return FoundRegister->second;

  return NULL;
}

Register* BitralContext::addSubRegister(Register* base, Register::Interval intv, const std::string& name) {

  Register* NewRegister = new Register(base, intv);
  Registers[name] = NewRegister;

  return NewRegister;
}

void BitralContext::addMapping(llvm::GlobalVariable* GV, void* address) {

 CompState.ExecEngine->addGlobalMapping(GV, address); 

}

//ConstantMemoryAddress BitralContext::getConstantMemoryAddress(boost::uint16_t bit_size, 
//                                                              boost::uint64_t address) {
/*ConstantMemoryAddress BitralContext::getConstantMemoryAddress(const Immediate& immediate) {
  return ConstantMemoryAddress(immediate); 
}*/

BitralContext::BitralContext() : CompState(llvm::getGlobalContext()) {
  llvm::InitializeNativeTarget();
  CompState.Module = new llvm::Module("BitralModule", CompState.LLVMCtx);
  CompState.ExecEngine = llvm::EngineBuilder(CompState.Module).create();
}
 
BitralContext::~BitralContext() {
  for (RegisterMapIterator I = Registers.begin(), E = Registers.end(); I != E; ++I)
    delete I->second;
}
