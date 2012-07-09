#ifndef __BITRAL_REGISTER_H__
#define __BITRAL_REGISTER_H__

#include <Operand.h>
#include <BitralConfig.h>

namespace Bitral {

class RegisterMemoryAddress;

class Register : public Operand {
  friend class RegisterMemoryAddress;
public:
 Register(std::uint16_t bit_size) : Operand(bit_size, NULL) {} 
};

}

#endif
