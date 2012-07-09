#ifndef __BITRAL_REGISTER_H__
#define __BITRAL_REGISTER_H__

#include <Operand.h>
#include <BitralConfig.h>

namespace Bitral {

class Register : public Operand {
public:
 Register() : Operand(0, NULL) {} 
};

}

#endif
