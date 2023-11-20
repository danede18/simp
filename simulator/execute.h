#ifndef EXECUTE_H
#define EXECUTE_H

#include "global_vars.h"

void execute(void);

// defenitions for the functions that perform the opration of each opcode.

void add(void);

void sub(void);

void and(void);

void or(void);

void sll(void);

void sra(void);

void srl(void);

void beq(void);

void bne(void);

void blt(void);

void bgt(void);

void ble(void);

void bge(void);

void jal(void);

void lw(void);

void sw(void);

void reti(void);

void in(void);

void out(void);

void halt(void);


#endif