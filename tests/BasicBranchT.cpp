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
#include <ConstantMemoryAddress.h>
#include <CodeRegion.h>
#include <cassert>
#undef NDEBUG
//#define DEBUG

using namespace Bitral;

boost::uint32_t reg_var = 100;
boost::uint32_t reg_var2 = 200;
boost::uint8_t mem[100];

int main() {

  BitralContext b;

  Register* reg = b.addRegister(32, "A", &reg_var);
  b.setMemorySpace(mem, sizeof(mem));
  CodeRegion* Region = b.createNewCodeRegion(ConstantMemoryAddress(Immediate(b, 32, 0)));
  ComparisonResult Condition = Region->createComparison(ComparisonResult::LEQUAL, Immediate(b, 32, 0), Immediate(b, 32, 1));
  Region->increaseMemoryPosition(4);
  //ComparisonResult Condition = BranchCondition::TRUE;
  //ConstantMemoryAddress branch_trgt = Region->createOffsetConditionalBranch(Condition, 8);
  Region->createOffsetConditionalBranch(Condition, 8);
/*  Region->increaseMemoryPosition(4);
  Region->createMove(Immediate(b, 32, 1), reg);
  Region->setMemoryPosition(branch_trgt);
  Region->createMove(Immediate(b, 32, 0), reg);
  */
  Region->closeRegion();
//  b.printModule("/home/hades/module.s");
  CodeRegion::CodePointer Code = Region->compile(); 
  assert(reg_var == 100);
  Code();
  std::cout << reg_var << std::endl;
  assert(reg_var == 0);

  return 0;

}
