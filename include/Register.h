#ifndef __BITRAL_REGISTER_H__
#define __BITRAL_REGISTER_H__

#include <string>
#include <llvm/Support/IRBuilder.h>
#include <MemoryStoredOperand.h>
#include <BitralConfig.h>
#include <llvm/GlobalVariable.h>

namespace llvm {
class Value;
}

namespace Bitral {

class RegisterMemoryAddress;
class BitralContext;
class CodeRegion;
class CompilerState;

class Register : public MemoryStoredOperand {
  //friend class RegisterMemoryAddress;
  friend class BitralContext;

public:
  struct Interval {
    boost::uint16_t Begin;
    boost::uint16_t End;
    Interval() : Begin(0), End(0) {}
    Interval(boost::uint16_t begin, boost::uint16_t end) : Begin(begin), End(end) {}
  };
//  virtual void setValue(CodeRegion* region, llvm::Value* val);
  virtual void generateLoadingCode(llvm::IRBuilder<>& builder);
  virtual void generateStoringCode(llvm::IRBuilder<>& builder) const;
  virtual DestinationOperand* clone();

private:
  Register* BaseReg;
  Interval Part;
  llvm::GlobalVariable* InitGV(CompilerState& c_state, void* address, boost::uint16_t bit_size);
  Register(CompilerState& c_state, void* address, boost::uint16_t bit_size) : 
                              MemoryStoredOperand(bit_size, InitGV(c_state, address, bit_size)), 
                              BaseReg(NULL) {} 
  Register(Register* base_reg, Interval ival) : MemoryStoredOperand(ival.End-ival.Begin, base_reg->RegGV), 
                                                BaseReg(base_reg), Part(ival) {} 
  Register(const Register& to_copy) : MemoryStoredOperand(*this), BaseReg(to_copy.BaseReg), 
                                      Part(to_copy.Part)  {}
};

}

#endif
