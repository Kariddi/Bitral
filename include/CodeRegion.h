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
#include <utility>
#include <BitralConfig.h>

namespace Bitral {

class BitralContext;
class CompilerState;

struct ComparisonResult {
  llvm::Value* CompResult;
  ComparisonResult(llvm::Value* comp_result) : CompResult(comp_result) {}
};

struct InstructionBlock {
  llvm::BasicBlock* Block;
  ConstantMemoryAddress Branch;
  InstructionBlock(llvm::BasicBlock* ib, ConstantMemoryAddress cma) : Block(ib), Branch(cma) {}
};

class CodeRegion {
  friend class BitralContext;
  typedef std::vector<InstructionBlock*> InstructionVector;
  typedef boost::unordered_map<ConstantMemoryAddress, InstructionVector*> InstructionMap;
  typedef boost::unordered_map<ConstantMemoryAddress, ConstantMemoryAddress> CAddrMap;
  typedef InstructionVector::iterator InstructionVectorIterator;
  typedef InstructionMap::iterator InstructionMapIterator;
  typedef CAddrMap::iterator CAddrMapIterator;
  typedef std::pair<ConstantMemoryAddress, ConstantMemoryAddress> CAddrPair;
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

  ConstantMemoryAddress CurrentPos;
  ConstantMemoryAddress CurrentBranch;
  llvm::Function* RegionFunc;
  llvm::BasicBlock* PreviousBB;
  llvm::IRBuilder<> Builder;
/*  llvm::LLVMContext& LLVMCtx;
  llvm::Module* Module;
  llvm::ExecutionEngine* ExecEngine;*/
  CompilerState CompState;
  InstructionMap AddressToInstructions;
  CAddrMap ActiveBranches;
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
  CodeRegion(CompilerState& c_state, ConstantMemoryAddress initial_pos);
public:
  typedef void(*CodePointer)();
  ~CodeRegion();
  bool setMemoryPosition(ConstantMemoryAddress new_pos);
  bool increaseMemoryPosition(boost::int16_t delta);
//ACTIONS
  void createXOR(const Operand& src, DestinationOperand* dst);
  void closeRegion();
  CodePointer compile(); 

};

}

#endif
