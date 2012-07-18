#ifndef __BITRAL_CODEREGION_H__
#define __BITRAL_CODEREGION_H__

#include <boost/unordered_map.hpp>
//#include <unordered_set>
#include <llvm/Function.h>
#include <llvm/Instruction.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>
#include <DestinationOperand.h>
#include <BitralContext.h>
#include <llvm/Support/IRBuilder.h>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;
class CompilerState;
//class DestinationOperand;

class CodeRegion {
  friend class BitralContext;
  typedef std::vector<llvm::BasicBlock*> InstructionVector;
  typedef boost::unordered_map<MemoryPtr, InstructionVector*> InstructionMap;
  typedef InstructionMap::iterator InstructionMapIterator;
public:
//  typedef std::unordered_map<Operand::IdType, DestinationOperand*> DestOpMap;
//  typedef DestOpMap::iterator DestOpMapIterator;
private:
/*  class BranchTargets {
    friend class CodeRegion;
    CodeRegion::DestOpMap* UsedMap;
    
  public:
    MemoryPtr Taken;
    MemoryPtr NotTaken;
    BranchTargets(CodeRegion::DestOpMap* map, MemoryPtr tkn, MemoryPtr ntkn) : UsedMap(map), Taken(tkn),
                                                                                NotTaken(ntkn) {}
    ~BranchTargets() {
      for (auto I = UsedMap->begin(), E = UsedMap->end(); I != E; ++I)
        delete I->second;
      delete UsedMap;
    }
  };
*/
//  typedef std::unordered_map<MemoryPtr, BranchTargets*> BranchMap;

  MemoryPtr CurrentPos;
  llvm::Function* RegionFunc;
  llvm::BasicBlock* PreviousBB;
  llvm::IRBuilder<> Builder;
/*  llvm::LLVMContext& LLVMCtx;
  llvm::Module* Module;
  llvm::ExecutionEngine* ExecEngine;*/
  CompilerState CompState;
  InstructionMap AddressToInstructions;
  //llvm::BasicBlock* CurrentFrontier;
  //BranchMap Branches;
  InstructionVector* CurrentVector;
  //DestOpMap* CurrentUsed;

  llvm::BasicBlock* advanceBB();
  void writeOperand(DestinationOperand* dst, llvm::Value* val);
  llvm::Value* readOperand(const Operand* src);
  //DestinationOperand* getUpdateDst(DestinationOperand* dst);
  //const Operand* getSource(const Operand* src);
  //void advanceBranch();
  CodeRegion(CompilerState& c_state, MemoryPtr initial_pos);
public:
  typedef void(*CodePointer)();
  ~CodeRegion();
//  bool setMemoryPosition(MemoryPtr new_pos);
  bool increaseMemoryPosition(boost::int16_t delta);
//ACTIONS
  void createXOR(const Operand* src, DestinationOperand* dst);
  void closeRegion();
  CodePointer compile(); 

};

}

#endif
