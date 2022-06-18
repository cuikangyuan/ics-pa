#ifndef __CPU_IFETCH_H__

#include <memory/vaddr.h>

//取指
/*
0x1234 小端架构 字节序如下，内存起始地址是x
x   x+1  x+2  x+3
+----+----+----+----+
| 34 | 12 | 00 | 00 |
+----+----+----+----+

vaddr_ifetch这行代码会将34 12 00 00这个字节序列原封不动地从内存读入imm变量中, 
主机的CPU会按照小端方式来解释这一字节序列, 于是会得到0x1234, 符合我们的预期结果
*/
static inline uint32_t instr_fetch(vaddr_t *pc, int len) {
  //eg: 反编译 80000000:	00000413          	li	s0,0
  //instr = 1043(10进制)(0x413) 
  uint32_t instr = vaddr_ifetch(*pc, len);
  (*pc) += len;
  return instr;
}

#endif
