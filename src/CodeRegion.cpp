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
#include <iostream>
#include <CodeRegion.h>

using namespace Bitral;

llvm::BasicBlock* CodeRegion::advanceBB() {
//Create a new BasicBlock and make an unconditional branch from the previous one to the new one
  llvm::BasicBlock* BB = llvm::BasicBlock::Create(CompState.LLVMCtx, "", RegionFunc);
  llvm::BranchInst::Create(BB, PreviousBB);
  CurrentVector->push_back(InstructionBlock(BB, CurrentBranch));
  PreviousBB = BB;

  return BB;

}

void CodeRegion::insertBranch(const InstructionBlock& taken, const InstructionBlock& not_taken) {
  CAddrMapIterator It = ActiveBranches.find(taken.Address);
  if (It != ActiveBranches.end())
    It->second = taken.Address;
  else
    ActiveBranches.insert(CAddrPair(taken.Address, taken.Address));
  CurrentVector->push_back(not_taken);
  InstructionVector* NewIV = new InstructionVector();
  NewIV->push_back(taken);
  AddressToInstructions[taken.Address] = NewIV; 
  PreviousBB = not_taken.Block;
}

llvm::BasicBlock* CodeRegion::linkBranch(const ConstantMemoryAddress& branch_addr) const {
  InstructionMapConstIterator It = AddressToInstructions.find(branch_addr);
  if (branch_addr == CurrentPos || It == AddressToInstructions.end())
    //Doesn't exist a BB at that address in the current code region
    return llvm::BasicBlock::Create(CompState.LLVMCtx, "", RegionFunc);
  else
    //Exists a ... creating a new BB
    return It->second->front().Block;
}

void CodeRegion::writeOperand(DestinationOperand* dst, llvm::Value* val) {
   
  dst->setValue(Builder, val);
}

llvm::Value* CodeRegion::readOperand(const Operand* src) {

  return src->getValue(Builder);

}

CodeRegion::CodeRegion(CompilerState& c_state, ConstantMemoryAddress initial_pos) : 
                       CurrentPos(initial_pos), CurrentBranch(initial_pos), 
                       Builder(c_state.LLVMCtx), CompState(c_state), 
                       CurrentVector(new InstructionVector()) {

//Function Creation

  llvm::FunctionType* NewFuncTy = llvm::FunctionType::get(llvm::Type::getVoidTy(CompState.LLVMCtx), 
                                                          std::vector<llvm::Type*>(), false);

  RegionFunc = llvm::Function::Create(NewFuncTy, llvm::Function::ExternalLinkage, "", 
                                                   CompState.Module);
//Entry BB Creation
  llvm::BasicBlock* BB = llvm::BasicBlock::Create(CompState.LLVMCtx, "", RegionFunc);
  Builder.SetInsertPoint(BB);
  CurrentVector->push_back(InstructionBlock(BB, initial_pos));
  AddressToInstructions[initial_pos] = CurrentVector;
  ActiveBranches.insert(CAddrPair(CurrentBranch, initial_pos));
  PreviousBB = BB;
}

CodeRegion::~CodeRegion() {

  for (InstructionMapIterator I = AddressToInstructions.begin(), E = AddressToInstructions.end(); I != E; ++I) 
    delete I->second;
}


bool CodeRegion::setMemoryPosition(const ConstantMemoryAddress& new_pos) {
  CurrentPos = new_pos;
  InstructionMapIterator MapIt = AddressToInstructions.find(CurrentPos);
  if (MapIt != AddressToInstructions.end()) {
    CurrentVector = MapIt->second;
    CurrentBranch = CurrentVector->back().Address;
    CAddrMapIterator It = ActiveBranches.find(CurrentBranch);
    PreviousBB = CurrentVector->back().Block;
    if (It->second == CurrentPos) {
      Builder.SetInsertPoint(CurrentVector->back().Block);
      return true;
    } else
      return false;
  } else {
    CurrentVector = new InstructionVector();
    AddressToInstructions[CurrentPos] = CurrentVector;
    CAddrMapIterator It = ActiveBranches.find(CurrentBranch);
    It->second = CurrentPos;
    llvm::BasicBlock* NewBB = advanceBB();
    Builder.SetInsertPoint(NewBB);
    CurrentVector->push_back(InstructionBlock(NewBB, CurrentBranch));
    PreviousBB = NewBB;
    return true;
  }

}

//Return true if instructions can be added at this position
bool CodeRegion::increaseMemoryPosition(boost::int16_t delta) {
  return setMemoryPosition(CurrentPos + delta);
}

void CodeRegion::setBranch(const ConstantMemoryAddress& new_branch) {
  CAddrMapIterator It = ActiveBranches.find(new_branch);
  if (It != ActiveBranches.end()) {
    CurrentBranch = new_branch;
    CurrentPos = It->second;
    CurrentVector = AddressToInstructions.find(CurrentPos)->second;
    Builder.SetInsertPoint(CurrentVector->back().Block);
    PreviousBB = CurrentVector->back().Block; 

  }
 
}
void CodeRegion::createXOR(const Operand& src, DestinationOperand* dst) {
  llvm::Value* val = Builder.CreateXor(readOperand(&src), readOperand(dst));
  writeOperand(dst, val);
}

void CodeRegion::createMove(const Operand& src, DestinationOperand* dst) {
  writeOperand(dst, readOperand(&src));
}

void CodeRegion::createAdd(const Operand& src, DestinationOperand* dst) {
  llvm::Value* val = Builder.CreateAdd(readOperand(&src), readOperand(dst));
  writeOperand(dst, val);
}

ComparisonResult CodeRegion::createComparison(ComparisonResult::Type type, const Operand& op1,
                                              const Operand& op2) {
  llvm::Value* result_val = NULL;
  switch (type) {
  case ComparisonResult::LESS:
    result_val = Builder.CreateICmpSLT(readOperand(&op1), readOperand(&op2));
    break;
  case ComparisonResult::LEQUAL:
    result_val = Builder.CreateICmpSLE(readOperand(&op1), readOperand(&op2));
    break;
  case ComparisonResult::EQUAL:
    result_val = Builder.CreateICmpEQ(readOperand(&op1), readOperand(&op2));
    break;
  case ComparisonResult::GEQUAL:
    result_val = Builder.CreateICmpSGE(readOperand(&op1), readOperand(&op2));
    break;
  case ComparisonResult::GREATER:
    result_val = Builder.CreateICmpSGT(readOperand(&op1), readOperand(&op2));
    break;
  }
  ComparisonResult result(result_val);

  return result;
}

ConstantMemoryAddress CodeRegion::createOffsetConditionalBranch(ComparisonResult comparison, 
                                               boost::int16_t offset) {
  ConstantMemoryAddress TakenAddress = CurrentPos + offset;
  llvm::BasicBlock* BBTkn = linkBranch(TakenAddress);
  llvm::BasicBlock* BBNTkn = linkBranch(CurrentPos);
  llvm::BranchInst::Create(BBTkn, BBNTkn, comparison.CompResult, CurrentVector->back().Block);
  insertBranch(InstructionBlock(BBTkn, TakenAddress), InstructionBlock(BBNTkn, CurrentBranch));
  Builder.SetInsertPoint(BBNTkn);
  
  return TakenAddress;
}

void CodeRegion::closeRegion() {
  for (CAddrMapIterator I = ActiveBranches.begin(), E = ActiveBranches.end(); I != E; ++I) {
    InstructionMapIterator It = AddressToInstructions.find(I->second);
    if (It != AddressToInstructions.end()) {
      InstructionVector* IV = AddressToInstructions.find(I->second)->second;
      Builder.SetInsertPoint(IV->back().Block);
      Builder.CreateRetVoid();
    }
  }
}

CodeRegion::CodePointer CodeRegion::compile() {

  return reinterpret_cast<CodePointer>(CompState.ExecEngine->getPointerToFunction(RegionFunc));
} 
