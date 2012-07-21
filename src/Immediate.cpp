#include <llvm/Constants.h>
#include <BitralContext.h>
#include <Immediate.h>

using namespace Bitral;

Immediate::Immediate(BitralContext& context, boost::uint16_t bit_size, boost::uint64_t value) : Operand(bit_size, 
                                                                  llvm::ConstantInt::get(
                                                                  llvm::IntegerType::get(
                                                                        context.getCompilerContext(),
                                                                        bit_size), value)) {}
