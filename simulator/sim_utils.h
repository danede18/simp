#ifndef SIM_UTILS_H
#define SIM_UTILS_H

#include "global_vars.h"

int get_bits(int n, int mask, unsigned int num);

int get_imm_bits(int n, int mask, int num);

void fetch(void);

void decode(void);

void clk(void);

void timer(void);

void interrupt(void);



#endif
