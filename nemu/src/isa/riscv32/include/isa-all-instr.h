#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(inv) f(addi) f(jal) f(auipc) f(jalr) \
        f(add) f(sub) f(sltiu) f(beq) f(bne) f(nemu_trap)
//t0, t1, ... - 只能在RTL伪指令的实现过程中存放中间结果
//s0, s1, ... - 只能在译码辅助函数和执行辅助函数的实现过程中存放中间结果
//每个执行辅助函数都需要有一个标识该指令的ID以及一个表格辅助函数与之相对应, 这一点是通过一系列宏定义来实现的
def_all_EXEC_ID();
