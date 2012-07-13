#ifndef __BITRAL_IMMEDIATE_H__
#define __BITRAL_IMMEDIATE_H__

#include <Operand.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;

class Immediate : public Operand {

  friend class BitralContext;
public:
  Immediate(BitralContext& context, std::uint16_t bit_size, std::uint64_t value); 
};

}

#endif
