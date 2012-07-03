#ifndef __BITRAL_OPERAND_H__
#define __BITRAL_OPERAND_H__
#include <BitralConfig.h>

namespace Bitral {

class Operand {

  std::uint16_t BitSize;
public:
  virtual void add(Operand* addend) = 0;
  virtual Comparison* compare(Operand* op) = 0;
  virtual void subtract(Operand* addend) = 0;
};

}

#endif
