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


#ifndef __BITRAL_BITRALCONTEXT_H__
#define __BITRAL_BITRALCONTEXT_H__

#include <string>
#include <cstring>
#include <boost/unordered_map.hpp>
#include <llvm/LLVMContext.h>
#include <llvm/GlobalValue.h>
#include <llvm/Module.h>
#include <llvm/Support/raw_ostream.h>
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
  llvm::GlobalValue* MemorySpace;

public:
  RegisterMapIterator reg_begin() { return Registers.begin(); }
  RegisterMapIterator reg_end() { return Registers.end(); }
  CodeRegion* createNewCodeRegion(ConstantMemoryAddress starting_address);
  void setMemorySpace(void* memory, boost::uint64_t size);
  llvm::GlobalValue* getMemorySpace() const;
//  Register* addRegister(boost::uint16_t bit_size, const std::string& name);
  Register* addRegister(boost::uint16_t bit_size, const std::string& name, void* memory_map_location);
  Register* getRegister(const std::string& name) const;
  Register* addSubRegister(Register* base, Register::Interval intv, const std::string& name);
  void addMapping(llvm::GlobalVariable* GV, void* address);
  const CompilerState& getCompilerState() const { return CompState; }
  llvm::LLVMContext& getCompilerContext() const { return CompState.LLVMCtx; }
  void printModule(const std::string& file_name) const { 
    std::string Error;
    llvm::raw_fd_ostream FileStream(file_name.c_str(), Error);
    CompState.Module->print(FileStream, NULL);
  }

  BitralContext();
  ~BitralContext(); 
};

}

#endif
