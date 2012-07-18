#ifndef __BITRAL_COMPILER_STATE_H__
#define __BITRAL_COMPILER_STATE_H__

namespace llvm {

  class LLVMContext;
  class Module;
  class ExecutionEngine;

}

namespace Bitral {

class CompilerState {
/*    CompilerState(llvm::LLVMContext& ctx, llvm::Module* mod, llvm::ExecutionEngine* exec) : LLVMCtx(ctx), 
                                                                                            Module(mod),
                                                                                            ExecEngine(exec) {}*/
    friend class BitralContext;
    CompilerState(llvm::LLVMContext& ctx) : LLVMCtx(ctx), Module(NULL), ExecEngine(NULL) {}
  public:
    llvm::LLVMContext& LLVMCtx;
    llvm::Module* Module;
    llvm::ExecutionEngine* ExecEngine; 
};

}

#endif
