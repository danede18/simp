#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <stdio.h>

// struct to hold the relevant fields of an instruction
struct instruction
{
    unsigned int opcode;
    unsigned int rd;
    unsigned int rs;
    unsigned int rt;
    int imm;
};


extern int mem[512];
extern int reg[16];
extern unsigned int ioreg[14];
extern int pc;
extern int reti_flag;
extern int inst_code;
extern int timer_turn_on;
extern struct instruction inst;
extern FILE* curr_file;
extern int cycles;

#endif