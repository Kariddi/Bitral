#ifndef __BITRAL_MEMORY_STORED_OPERAND_H__
#define __BITRAL_MEMORY_STORED_OPERAND_H__

#include <llvm/GlobalVariable.h>
#include <llvm/Support/IRBuilder.h>
#include <DestinationOperand.h>

namespace Bitral {

class MemoryStoredOperand : public DestinationOperand {

protected:
  llvm::GlobalVariable* RegGV;
public:
  virtual bool isMemoryStored() { return true; }
  virtual void generateLoadingCode(llvm::IRBuilder<>& builder) = 0;
  virtual void generateStoringCode(llvm::IRBuilder<>& builder) const = 0;
  MemoryStoredOperand(boost::uint16_t bit_size, llvm::GlobalVariable* op_value) : DestinationOperand(bit_size, op_value), RegGV(op_value) {}

};

}

#endif
