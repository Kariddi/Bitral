#include <BitralContext.h>
#include <Register.h>
#include <CompilerState.h>

using namespace Bitral;

/*void Register::setValue(CodeRegion* region, llvm::Value* val) {

  OperandValue = val;

}*/
llvm::GlobalVariable* Register::InitGV(CompilerState& c_state, void* address, 
                                       boost::uint16_t bit_size) {
    llvm::GlobalVariable* RegGV = llvm::dyn_cast<llvm::GlobalVariable>(c_state.Module->getOrInsertGlobal("", 
                                               llvm::Type::getIntNTy(c_state.LLVMCtx, bit_size)));
    c_state.ExecEngine->addGlobalMapping(RegGV, address);
    return RegGV;
}

void Register::generateLoadingCode(llvm::IRBuilder<>& builder) {
  OperandValue = builder.CreateLoad(RegGV);
}

void Register::generateStoringCode(llvm::IRBuilder<>& builder) const {
  builder.CreateStore(OperandValue, RegGV);
}

DestinationOperand* Register::clone() {

  return new Register(*this); 

}
