#ifndef __BITRAL_BITRALCONTEXT_H__
#define __BITRAL_BITRALCONTEXT_H__

#include <string>
#include <unordered_map>
#include <llvm/LLVMContext.h>
#include <Register.h>
#include <CodeRegion.h>
#include <ConstantMemoryAddress.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext {

typedef std::unordered_map<std::uint32_t, Register*> RegisterMap;
typedef RegisterMap::iterator RegisterMapIterator;
typedef RegisterMap::const_iterator RegisterMapConstIterator;
typedef std::unordered_map<std::uint64_t, CodeRegion*> CodeRegionMap;
typedef CodeRegionMap::iterator CodeRegionMapIterator;
typedef CodeRegionMap::const_iterator CodeRegionMapConstIterator;

  RegisterMap Registers;
  llvm::LLVMContext LLVMCtx;
  friend class ConstantMemoryAddress;

public:
  CodeRegion* createNewCodeRegion(const ConstantMemoryAddress& starting_address);
  Register* addRegister(std::uint16_t bit_size, std::uint32_t code);
  Register* addRegister(std::uint16_t bit_size, std::uint32_t code, const void* memory_map_location);
  Register* getRegister(std::uint32_t name) const;
  ConstantMemoryAddress getConstantMemoryAddress(std::uint16_t bit_size, std::uint64_t address);
  ~BitralContext(); 
};

}

#endif
