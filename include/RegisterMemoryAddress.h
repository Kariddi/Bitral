#ifndef __BITRAL_REGISTER_MEMORY_ADDRESS_H__
#define __BITRAL_REGISTER_MEMORY_ADDRESS_H__


namespace Bitral {

class Register;

class RegisterMemoryAddress : public MemoryAddress {

  Register* Base;
  Register* Index;
  Immediate Scale;
  Immediate Displacement;
  //friend class BitralContext;

public:
  RegisterMemoryAddress(BitralContext& context, Register* base_reg);

  RegisterMemoryAddress(BitralContext& context, Register* base_reg, Register* index, const Immediate& scale);
  RegisterMemoryAddress(BitralContext& context, Register* base_reg, Register* index, 
                        const Immediate& scale, const Immediate& displacement);
  RegisterMemoryAddress(BitralContext& context, Register* base_reg, const Immediate& displacement);

  virtual boost::uint16_t getBitSize();
};

}

#endif
