#ifndef __BITRAL_IMMEDIATE_H__
#define __BITRAL_IMMEDIATE_H__

#include <Operand.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;

class Immediate : public Operand {

//  friend class BitralContext;
public:
  Immediate(BitralContext& context, boost::uint16_t bit_size, boost::uint64_t value); 
};

}

#endif
