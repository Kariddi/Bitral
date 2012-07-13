#ifndef __BITRAL_REGISTER_H__
#define __BITRAL_REGISTER_H__

#include <string>
#include <DestinationOperand.h>
#include <BitralConfig.h>

namespace Bitral {

class RegisterMemoryAddress;
class BitralContext;

class Register : public DestinationOperand {
  friend class RegisterMemoryAddress;
  friend class BitralContext;

public:
 struct Interval {
   uint16_t Begin;
   uint16_t End;
   Interval(uint16_t begin, uint16_t end) : Begin(begin), End(end) {}
 };
private:
  Register(std::uint16_t bit_size) : DestinationOperand(bit_size, NULL) {} 
  Register(Register* base_reg, Interval ival) : DestinationOperand(ival.End-ival.Begin, NULL) {} 
};

}

#endif
