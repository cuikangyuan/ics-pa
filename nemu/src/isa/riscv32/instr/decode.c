#include "../local-include/reg.h"
#include <cpu/ifetch.h>
#include <isa-all-instr.h>

def_all_THelper();

static uint32_t get_instr(Decode *s) {
  return s->isa.instr.val;
}

// decode operand helper
//def_DopHelper 译码操作数辅助函数
#define def_DopHelper(name) \
  void concat(decode_op_, name) (Decode *s, Operand *op, word_t val, bool flag)

static def_DopHelper(i) {
  op->imm = val;
}

static def_DopHelper(r) {
  bool is_write = flag;
  static word_t zero_null = 0;
  op->preg = (is_write && val == 0) ? &zero_null : &gpr(val);
}

static def_DHelper(I) {
  decode_op_r(s, id_src1, s->isa.instr.i.rs1, false);
  decode_op_i(s, id_src2, s->isa.instr.i.simm11_0, false);
  decode_op_r(s, id_dest, s->isa.instr.i.rd, true);
}

// def_DHelper : 
//译码辅助函数 会依赖译码操作数辅助函数 
//把指令中的操作数信息记录在s的dest(目的操作数),src1(源操作数),src2(源操作数)中
static def_DHelper(U) {
  decode_op_i(s, id_src1, s->isa.instr.u.imm31_12 << 12, true);
  decode_op_r(s, id_dest, s->isa.instr.u.rd, true);
}

static def_DHelper(S) {
  decode_op_r(s, id_src1, s->isa.instr.s.rs1, false);
  sword_t simm = (s->isa.instr.s.simm11_5 << 5) | s->isa.instr.s.imm4_0;
  decode_op_i(s, id_src2, simm, false);
  decode_op_r(s, id_dest, s->isa.instr.s.rs2, false);
}

def_THelper(load) {
  //这里def_INSTR_TAB也是一条字符串匹配规则, 但它并不需要调用译码辅助函数. 这条规则描述了"在load类型指令中, 如果funct3为010, 则为lw指令
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", lw);
  return EXEC_ID_inv;
}

def_THelper(store) {
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", sw);
  return EXEC_ID_inv;
}

def_THelper(cal_imm) {
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", addi);
  return EXEC_ID_inv;
}

/*
  def_INSTR_IDTAB 对于lui指令宏展开
  do {
    uint32_t key, mask, shift;
    pattern_decode("??????? ????? ????? ??? ????? 01101 11",
                   (sizeof("??????? ????? ????? ??? ????? 01101 11") - 1), &key,
                   &mask, &shift);
    if (((get_instr(s) >> shift) & mask) == key) {
      {
        decode_U(s, 0);
        return table_lui(s);
      };
    }
  } while (0);

  table_lui() 直接返回标识lui指令的唯一ID ，这个ID作为译码结果的返回值
  从table_main方法返回后
  在fetch_decode()中用这个ID值索引g_exec_table数组
*/

//表格辅助函数 主表
def_THelper(main) {
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00000 11", I     , load);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01000 11", S     , store);
  //def_INSTR_IDTAB 此类需要进一步调用译码辅助函数，译码操作数辅助函数
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 01101 11", U     , lui);
  def_INSTR_IDTAB("??????? ????? ????? ??? ????? 00100 11", I     , cal_imm);
  //def_INSTR_TAB 不需要调用译码辅助函数
  def_INSTR_TAB  ("??????? ????? ????? ??? ????? 11010 11",         nemu_trap);
  return table_inv(s);
};

int isa_fetch_decode(Decode *s) {
  s->isa.instr.val = instr_fetch(&s->snpc, 4);
  int idx = table_main(s);
  return idx;
}
