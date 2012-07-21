#ifndef __BITRAL_BITRALCONTEXT_H__
#define __BITRAL_BITRALCONTEXT_H__

#include <string>
#include <cstring>
#include <boost/unordered_map.hpp>
#include <llvm/LLVMContext.h>
#include <llvm/GlobalValue.h>
#include <llvm/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <ConstantMemoryAddress.h>
#include <RegisterMemoryAddress.h>
#include <Register.h>
#include <CompilerState.h>
#include <BitralConfig.h>

namespace Bitral {

class CodeRegion;
class Register;

class BitralContext {
  typedef boost::unordered_map<std::string, Register*> RegisterMap;
  typedef RegisterMap::iterator RegisterMapIterator;
  typedef RegisterMap::const_iterator RegisterMapConstIterator;
  typedef boost::unordered_map<ConstantMemoryAddress, CodeRegion*> CodeRegionMap;
  typedef CodeRegionMap::iterator CodeRegionMapIterator;
  typedef CodeRegionMap::const_iterator CodeRegionMapConstIterator;

  RegisterMap Registers;
  CodeRegionMap CodeRegions;
/*  llvm::LLVMContext& LLVMCtx;
  llvm::Module* Module;
  llvm::ExecutionEngine* ExecEngine;*/
  CompilerState CompState;
//  llvm::GlobalValue* MemorySpace;

public:
  RegisterMapIterator reg_begin() { return Registers.begin(); }
  RegisterMapIterator reg_end() { return Registers.end(); }
  CodeRegion* createNewCodeRegion(ConstantMemoryAddress starting_address);
  void setMemorySpace(void* memory, boost::uint64_t size);
  llvm::GlobalValue* getMemorySpace();
//  Register* addRegister(boost::uint16_t bit_size, const std::string& name);
  Register* addRegister(boost::uint16_t bit_size, const std::string& name, void* memory_map_location);
  Register* getRegister(const std::string& name) const;
  Register* addSubRegister(Register* base, Register::Interval intv, const std::string& name);
  void addMapping(llvm::GlobalVariable* GV, void* address);
  llvm::LLVMContext& getCompilerContext() { return CompState.LLVMCtx; }
  BitralContext();
  ~BitralContext(); 
};

}

#endif
