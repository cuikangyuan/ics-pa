def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
}

def_EHelper(addi) {
  rtl_addi(s, ddest, dsrc1, id_src2->imm);
}

def_EHelper(auipc) {
  rtl_addi(s, ddest, &s->pc, id_src1->imm);
}

def_EHelper(jal) {
  rtl_addi(s, ddest, &s->pc, 4);
  rtl_addi(s, &s->dnpc, &s->pc, id_src1->imm);
}


def_EHelper(jalr) {
  rtl_addi(s, s0, &s->pc, 4);
  rtl_addi(s, &s->dnpc, dsrc1, id_src2->imm);
  rtl_andi(s, &s->dnpc, &s->dnpc, ~1);
  rtl_addi(s, ddest, s0, 0);
}

def_EHelper(add) {
  //add test : rs2: 10, rs1:18, rd: 10 
  rtl_add(s, ddest, dsrc1, dsrc2);
}