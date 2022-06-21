#include <isa.h>
#include "local-include/reg.h"

//https://en.wikichip.org/wiki/risc-v/registers
const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

#define REG_PER_LINE 4

void isa_reg_display() {
  int len = ARRLEN(regs);
  int i = 0;
  for (i = 0; i + REG_PER_LINE < len; i = i + REG_PER_LINE)
  {
      for (int j = i; j < i + REG_PER_LINE; j++)
      {
        printf("%-4s: 0x%-16x \t", regs[j], cpu.gpr[j]._32);
      }
      printf("\n");
  }

  for (int j = i; j < len; j++)
  {
      printf("%-4s: 0x%-16x \t", regs[j], cpu.gpr[j]._32);
  }
  printf("\n");
  printf("%-4s0x%-16x%-16d\n", "pc", cpu.pc, cpu.pc);
}

word_t isa_reg_str2val(const char *s, bool *success) {
  *success = true;
  if (strcmp(s, "pc") == 0)
  {
    return cpu.pc;
  }
  
  for (int i = 0; i < ARRLEN(regs); i++)
  {
    if (strcmp(s, regs[i]) == 0)
    {
      return cpu.gpr[i]._32;
    }
    
  }
  *success = false;
  return 0;
}
