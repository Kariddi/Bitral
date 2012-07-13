#ifndef __BITRAL_BITRALCONTEXT_H__
#define __BITRAL_BITRALCONTEXT_H__

#include <string>
#include <unordered_map>
#include <llvm/LLVMContext.h>
#include <Register.h>
#include <CodeRegion.h>
#include <ConstantMemoryAddress.h>
#include <RegisterMemoryAddress.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext {

typedef std::unordered_map<std::string, Register*> RegisterMap;
typedef RegisterMap::iterator RegisterMapIterator;
typedef RegisterMap::const_iterator RegisterMapConstIterator;
typedef std::unordered_map<std::uint64_t, CodeRegion*> CodeRegionMap;
typedef CodeRegionMap::iterator CodeRegionMapIterator;
typedef CodeRegionMap::const_iterator CodeRegionMapConstIterator;

  RegisterMap Registers;

public:
  llvm::LLVMContext LLVMCtx;
  CodeRegion* createNewCodeRegion(const ConstantMemoryAddress& starting_address);
  Register* addRegister(std::uint16_t bit_size, const std::string& name);
  Register* addRegister(std::uint16_t bit_size, const std::string& name, const void* memory_map_location);
  Register* getRegister(const std::string& name) const;
  Register* addSubRegister(Register* base, Register::Interval intv, const std::string& name);
  //Register* getSubRegister(const std::string& name) const;

//  ConstantMemoryAddress getConstantMemoryAddress(std::uint16_t bit_size, std::uint64_t address);
/*  Immediate getImmediate(std::uint16_t bit_size, std::uint64_t value) { 
    return Immediate(LLVMCtx, bit_size, value); 
  }
  ConstantMemoryAddress getConstantMemoryAddress(const Immediate& immediate);
  RegisterMemoryAddress getRegisterMemoryAddress(Register* base_reg) {
    return RegisterMemoryAddress(*this, base_reg);
  }
  RegisterMemoryAddress getRegisterMemoryAddress(Register* base_reg, Register* index, const Immediate& scale) {
    return RegisterMemoryAddress(*this, base_reg, index, scale);
  }
  RegisterMemoryAddress getRegisterMemoryAddress(Register* base_reg, Register* index, 
                                                 const Immediate& scale, const Immediate& displacement) {
    return RegisterMemoryAddress(*this, base_reg, index, scale, displacement);
  }
  RegisterMemoryAddress getRegisterMemoryAddress(Register* base_reg, const Immediate& displacement) {
    return RegisterMemoryAddress(*this, base_reg, displacement);
  }*/
  ~BitralContext(); 
};

}

#endif
