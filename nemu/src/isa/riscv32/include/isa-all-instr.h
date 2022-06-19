#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(inv) f(addi) f(auipc) f(nemu_trap)

//每个执行辅助函数都需要有一个标识该指令的ID以及一个表格辅助函数与之相对应, 这一点是通过一系列宏定义来实现的
def_all_EXEC_ID();
