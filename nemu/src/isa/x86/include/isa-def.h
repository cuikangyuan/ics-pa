#ifndef __ISA_X86_H__
#define __ISA_X86_H__

#include <common.h>

typedef struct
{

  struct
  {
    union
    {
      union
      {
        uint32_t _32;
        uint16_t _16;
        uint8_t _8[2];
      } gpr[8];

      struct
      {
        /* Do NOT change the order of the GPRs' definitions. */

        /* In NEMU, rtlreg_t is exactly uint32_t. This makes RTL instructions
         * in PA2 able to directly access these registers.
         */
        rtlreg_t eax;
        rtlreg_t edx;
        rtlreg_t ecx;
        rtlreg_t ebx;
        rtlreg_t ebp;
        rtlreg_t esi;
        rtlreg_t edi;
        rtlreg_t esp;
      };
    };
  };

  vaddr_t pc;
} x86_CPU_state;

#endif
