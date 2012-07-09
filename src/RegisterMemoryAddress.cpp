#include <algorithm>
#include <BitralContext.h>
#include <Register.h>
#include <Immediate.h>
#include <RegisterMemoryAddress.h>
using namespace Bitral;

RegisterMemoryAddress::RegisterMemoryAddress(BitralContext& context, Register* base_reg) : 
                                                                      Base(base_reg), Index(NULL), 
                                                                      Scale(context.getImmediate(0,0)),
                                                                      Displacement(context.getImmediate(0,0)) {}

RegisterMemoryAddress::RegisterMemoryAddress(BitralContext& context, Register* base_reg, 
                                             Register* index, const Immediate& scale) : 
                                             Base(base_reg), Index(index),
                                             Scale(scale), Displacement(context.getImmediate(0,0)) {}

RegisterMemoryAddress::RegisterMemoryAddress(BitralContext& context, Register* base_reg, Register* index, 
                                                                     const Immediate& scale, 
                                                                     const Immediate& displacement) : 
                                                                     Base(base_reg), Index(index), Scale(scale),
                                                                     Displacement(displacement) {}

RegisterMemoryAddress::RegisterMemoryAddress(BitralContext& context, Register* base_reg, 
                                             const Immediate& displacement) : Base(base_reg), Index(NULL), 
                                                                        Scale(context.getImmediate(0,0)),
                                                                        Displacement(displacement) {}

std::uint16_t RegisterMemoryAddress::getBitSize() {
    if (Index != NULL) {
      return std::max(Base->getBitSize(), std::max(Index->getBitSize(), 
                      std::max(Scale.getBitSize(), Displacement.getBitSize())));
    }
    
    return std::max(Base->getBitSize(), std::max(Scale.getBitSize(), Displacement.getBitSize())); 
}

