#include <BitralContext.h>
#include <CodeRegion.h>

using namespace Bitral;

llvm::BasicBlock* CodeRegion::advanceBB() {
//Create a new BasicBlock and make an unconditional branch from the previous one to the new one
/*  if (CurrentVector->size() > 0)
    OldBB = CurrentVector->back();*/
  llvm::BasicBlock* BB = llvm::BasicBlock::Create(CompState.LLVMCtx, "", RegionFunc);
  llvm::BranchInst::Create(BB, PreviousBB);
  CurrentVector->push_back(BB);
  PreviousBB = BB;

  return BB;

}

void CodeRegion::writeOperand(DestinationOperand* dst, llvm::Value* val) {
   
  dst->setValue(val);
}

llvm::Value* CodeRegion::readOperand(const Operand* src) {

  return src->getValue();

}

/*
DestinationOperand* CodeRegion::getUpdateDst(DestinationOperand* dst) {

  Operand::IdType Id = dst->getID();
  DestOpMapIterator MapIt = CurrentUsed->find(Id);
  if ( MapIt != CurrentUsed->end() )
    return MapIt->second;

  DestinationOperand* cloned_dst = dst->clone();
  (*CurrentUsed)[Id] = cloned_dst;

  return cloned_dst;

}
*/
/*
const Operand* CodeRegion::getSource(const Operand* src) {

  DestOpMapIterator MapIt = CurrentUsed->find(src->getID());
  if ( MapIt != CurrentUsed->end() )
    return MapIt->second;

  return src;

}
*/

/*
void CodeRegion::advanceBranch() {
  llvm::BasicBlock* CurrentBB = CurrentVector->back();
  BranchesSet->erase(old_frontier);
  BranchesSet->insert(CurrentBB);
}*/

CodeRegion::CodeRegion(CompilerState& c_state, MemoryPtr initial_pos) : 
                       CurrentPos(initial_pos), Builder(c_state.LLVMCtx), CompState(c_state), 
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
  CurrentVector->push_back(BB);
}

CodeRegion::~CodeRegion() {

 for (InstructionMapIterator I = AddressToInstructions.begin(), E = AddressToInstructions.end(); I != E; ++I)
   delete I->second;
/*
 for (auto I = Branches.begin(), E = Branches.end(); I != E; ++I)
   delete I->second;
*/
}

/*
bool CodeRegion::setMemoryPosition(MemoryPtr new_pos) {
  CurrentPos = new_pos;
  if (InstructionMap.find(new_pos) != InstructionMap.end()) {
    CurrentVector = *InstructionMap.find(new_pos);
    return false;
  }
  //advanceBranch(CurrentVector->back());
  CurrentVector = new InstructionVector();
  InstructionMap[CurrentPos] = CurrentVector;
  return true;
}*/

//Return true if instructions can be added at this position
bool CodeRegion::increaseMemoryPosition(boost::int16_t delta) {
  CurrentPos += delta;
  InstructionMapIterator MapIt = AddressToInstructions.find(CurrentPos);
  PreviousBB = CurrentVector->back();
  if (MapIt != AddressToInstructions.end()) {
    CurrentVector = MapIt->second;
    return false;
  }
  CurrentVector = new InstructionVector();
  AddressToInstructions[CurrentPos] = CurrentVector;
  return true;
}

void CodeRegion::createXOR(const Operand* src, DestinationOperand* dst) {
  llvm::BasicBlock* NewBB = advanceBB();
  Builder.SetInsertPoint(NewBB);
  CurrentVector->push_back(NewBB);
  if (dst->isMemoryStored())
    static_cast<MemoryStoredOperand*>(dst)->generateLoadingCode(Builder);
  llvm::Value* SrcVal = readOperand(src);
  llvm::Value* val = Builder.CreateXor(readOperand(src), readOperand(dst));
  //CurrentVector->push_back(val);
  writeOperand(dst, val);
  if (dst->isMemoryStored())
    static_cast<MemoryStoredOperand*>(dst)->generateStoringCode(Builder);
}

void CodeRegion::closeRegion() {
  Builder.CreateRetVoid();
}

CodeRegion::CodePointer CodeRegion::compile() {

  return reinterpret_cast<CodePointer>(CompState.ExecEngine->getPointerToFunction(RegionFunc));
} 
