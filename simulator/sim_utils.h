#ifndef SIM_UTILS_H
#define SIM_UTILS_H

#include "global_vars.h"

void intToHexCharArray(int num, char* hexArray);

int get_bits(int n, int mask, unsigned int num);

int get_imm_bits(int n, int mask, int num);

void load_mem(FILE* file);

void init(FILE* file);

void fetch(void);

void decode(void);

#endif
