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
/*  if (CurrentVector->size() > 0)
    OldBB = CurrentVector->back();*/
  llvm::BasicBlock* BB = llvm::BasicBlock::Create(CompState.LLVMCtx, "", RegionFunc);
  llvm::BranchInst::Create(BB, PreviousBB);
  CurrentVector->push_back(new InstructionBlock(BB, CurrentPos));
  PreviousBB = BB;

  return BB;

}

void CodeRegion::writeOperand(DestinationOperand* dst, llvm::Value* val) {
   
  dst->setValue(val);
}

llvm::Value* CodeRegion::readOperand(const Operand* src) {

  return src->getValue();

}

CodeRegion::CodeRegion(CompilerState& c_state, ConstantMemoryAddress initial_pos) : 
                       CurrentPos(initial_pos), CurrentBranch(initial_pos), 
                       Builder(c_state.LLVMCtx), CompState(c_state), 
                       CurrentVector(new InstructionVector()) {

//  Branches[initial_pos] = new BranchTargets(CurrentUsed, initial_pos, initial_pos);
//Function Creation

  llvm::FunctionType* NewFuncTy = llvm::FunctionType::get(llvm::Type::getVoidTy(CompState.LLVMCtx), 
                                                          std::vector<llvm::Type*>(), false);

  RegionFunc = llvm::Function::Create(NewFuncTy, llvm::Function::ExternalLinkage, "", 
                                                   CompState.Module);
//Entry BB Creation
  llvm::BasicBlock* BB = llvm::BasicBlock::Create(CompState.LLVMCtx, "", RegionFunc);
  Builder.SetInsertPoint(BB);
  CurrentVector->push_back(new InstructionBlock(BB, initial_pos));
  AddressToInstructions[initial_pos] = CurrentVector;
  ActiveBranches.insert(CAddrPair(CurrentBranch, initial_pos));
  PreviousBB = BB;
}

CodeRegion::~CodeRegion() {

  for (InstructionMapIterator I = AddressToInstructions.begin(), E = AddressToInstructions.end(); I != E; ++I) {
    for (InstructionVectorIterator I2 = I->second->begin(), E2 = I->second->end(); I2 != E2; ++I2)
      delete *I2;
    delete I->second;
  }
}


bool CodeRegion::setMemoryPosition(ConstantMemoryAddress new_pos) {
  CurrentPos = new_pos;
  InstructionMapIterator MapIt = AddressToInstructions.find(CurrentPos);
  PreviousBB = CurrentVector->back()->Block;
  if (MapIt != AddressToInstructions.end()) {
    CurrentVector = MapIt->second;
    return false;
  }
  CurrentVector = new InstructionVector();
  AddressToInstructions[CurrentPos] = CurrentVector;
  CAddrMapIterator It = ActiveBranches.find(CurrentBranch);
  if (It != ActiveBranches.end())
    It->second = CurrentPos;
  else
    ActiveBranches.insert(CAddrPair(CurrentBranch, CurrentPos));

  return true;

}

//Return true if instructions can be added at this position
bool CodeRegion::increaseMemoryPosition(boost::int16_t delta) {
  CurrentPos += delta;
  InstructionMapIterator MapIt = AddressToInstructions.find(CurrentPos);
  PreviousBB = CurrentVector->back()->Block;
  if (MapIt != AddressToInstructions.end()) {
    CurrentVector = MapIt->second;
    return false;
  }
  CurrentVector = new InstructionVector();
  AddressToInstructions[CurrentPos] = CurrentVector;
  CAddrMapIterator It = ActiveBranches.find(CurrentBranch);
  if (It != ActiveBranches.end())
    It->second = CurrentPos;
  else
    ActiveBranches.insert(CAddrPair(CurrentBranch, CurrentPos));

  return true;
}

void CodeRegion::createXOR(const Operand& src, DestinationOperand* dst) {
  llvm::BasicBlock* NewBB = advanceBB();
  Builder.SetInsertPoint(NewBB);
  //CurrentVector->push_back(new InstructionBlock(NewBB, CurrentPos));
  if (dst->isMemoryStored())
    static_cast<MemoryStoredOperand*>(dst)->generateLoadingCode(Builder);
  llvm::Value* SrcVal = readOperand(&src);
  llvm::Value* val = Builder.CreateXor(readOperand(&src), readOperand(dst));
  //CurrentVector->push_back(val);
  writeOperand(dst, val);
  if (dst->isMemoryStored())
    static_cast<MemoryStoredOperand*>(dst)->generateStoringCode(Builder);
}

ComparisonResult CodeRegion::createComparison(ComparisonResult::Type type, const Operand& op1,
                                              const Operand& op2) {
  llvm::BasicBlock* NewBB = advanceBB();
  Builder.SetInsertPoint(NewBB);
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

void CodeRegion::createOffsetConditionalBranch(ComparisonResult comparison, 
                                               boost::int16_t offset) {
//THIS IS SUPER PLACEHOLDER CODE!!!!!

  llvm::BasicBlock* NewBB = advanceBB();
  Builder.SetInsertPoint(NewBB);
  llvm::BasicBlock* BB = llvm::BasicBlock::Create(CompState.LLVMCtx, "", RegionFunc);
  llvm::BasicBlock* BB2 = llvm::BasicBlock::Create(CompState.LLVMCtx, "", RegionFunc);
  llvm::BranchInst::Create(BB, BB2, comparison.CompResult, NewBB);
  CAddrMapIterator It = ActiveBranches.find(CurrentPos+offset);
  if (It != ActiveBranches.end())
    It->second = CurrentPos+offset;
  else
    ActiveBranches.insert(CAddrPair(CurrentPos+offset, CurrentPos+offset));
  CurrentVector->push_back(new InstructionBlock(BB, CurrentBranch));
  InstructionVector* NewIV = new InstructionVector();
  NewIV->push_back(new InstructionBlock(BB2, CurrentPos+offset));
  AddressToInstructions[CurrentPos+offset] = NewIV; 
}

void CodeRegion::closeRegion() {
  for (CAddrMapIterator I = ActiveBranches.begin(), E = ActiveBranches.end(); I != E; ++I) {
    InstructionMapIterator It = AddressToInstructions.find(I->second);
    if (It != AddressToInstructions.end()) {
      InstructionVector* IV = AddressToInstructions.find(I->second)->second;
      Builder.SetInsertPoint(IV->back()->Block); 
      Builder.CreateRetVoid();
    }
  }
}

CodeRegion::CodePointer CodeRegion::compile() {

  return reinterpret_cast<CodePointer>(CompState.ExecEngine->getPointerToFunction(RegionFunc));
} 
