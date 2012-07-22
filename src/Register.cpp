/*  Copyright (c) 2012 Marcello Maggioni 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial 
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
CONTRACT, TORT OR OTHERWISE, RISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.

*/


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
