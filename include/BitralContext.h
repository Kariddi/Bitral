#ifndef __BITRAL_BITRALCONTEXT_H__
#define __BITRAL_BITRALCONTEXT_H__

#include <string>
#include <unordered_map>
#include <Register.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext {

typedef std::unordered_map<std::string, Register*> RegisterMap;
typedef RegisterMap::iterator RegisterMapIterator;

  RegisterMap Registers;

public:
  Register* addRegister(std::uint16_t bit_size, std::string name);
  Register* addRegister(std::uint16_t bit_size, std::string name, void* memory_map_location);
  Register* getRegister(std::string name);
  ~BitralContext(); 
};

}

#endif
