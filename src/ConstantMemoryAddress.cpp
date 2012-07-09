#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <BitralContext.h>
#include <ConstantMemoryAddress.h>

using namespace Bitral;

//ConstantMemoryAddress::ConstantMemoryAddress(llvm::LLVMContext& context, 
//                                             std::uint16_t bit_size, std::uint64_t address) : 
//                                             MemoryAddress(bit_size, 
//                                             llvm::ConstantInt::get(llvm::IntegerType::get(context, 
//                                             bit_size), address)), Address(address) {}

std::uint16_t ConstantMemoryAddress::getBitSize() { return ImmediateValue.getBitSize(); }
