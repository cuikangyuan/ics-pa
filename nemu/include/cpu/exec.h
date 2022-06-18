#ifndef __CPU_EXEC_H__
#define __CPU_EXEC_H__

#include <cpu/decode.h>

//执行辅助函数
#define def_EHelper(name) static inline void concat(exec_, name) (Decode *s)

#endif
