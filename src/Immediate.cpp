#include <llvm/Constants.h>
#include <BitralContext.h>
#include <Immediate.h>

using namespace Bitral;

Immediate::Immediate(BitralContext& context, std::uint16_t bit_size, std::uint64_t value) : Operand(bit_size, 
                                                                     llvm::ConstantInt::get(
                                                                     llvm::IntegerType::get(context.LLVMCtx, 
                                                                     bit_size), value)) {}
