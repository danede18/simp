#include "global_vars.h"

// gloabl variables to be used in the project

int mem[512];
int reg[16];
unsigned int ioreg[14];
int pc;
int reti_flag;
int inst_code;
int timer_turn_on;
struct instruction inst;
FILE* curr_file;
int cycles;