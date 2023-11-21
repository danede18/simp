#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "global_vars.h"
#include "sim_utils.h"

int get_bits(int n, int mask, unsigned int num) {
    // used to retrieve certain bits from an interger variable num.
    // the mask chooses which bits to select
    // perform logical right shift by n to put the bits to be LSBs
    num = num & mask;
    num = num >> n;
    return num;

}

int get_imm_bits(int n, int mask, int num) {
    // used to retrieve certain bits from an interger variable num.
    // the mask chooses which bits to select
    // perform logical right shift by n to put the bits to be LSBs
    num = num & mask;
    num = num >> n;

    // the imm value needs to be sign extended. If num after the right shift is >= 0b0100000000000 than it is a negative number so we add ones the the remaining MSBs.
    if (num >= 0x00000800) {// 0b0100000000000 

        mask = 0xFFFFF000;
        num = num | mask;

    }

    return num;

}

void fetch(void) {
    // fetch the instruction at PC from memory
    inst_code = mem[pc];

}

void decode(void) {
    // decode the instruction

    // get the opcode
    int opcode_mask = 0xFF000000; // 11111111000000000000000000000000
    int opcode_shift = 24;
    inst.opcode = get_bits(opcode_shift, opcode_mask, inst_code);

    // get the rd register
    int rd_mask = 0x00F00000; // 00000000111100000000000000000000
    int rd_shift = 20;
    inst.rd = get_bits(rd_shift, rd_mask, inst_code);

    // get the rs register
    int rs_mask = 0x000F0000; // 00000000000011110000000000000000
    int rs_shift = 16;
    inst.rs = get_bits(rs_shift, rs_mask, inst_code);

    // get the rt register
    int rt_mask = 0x0000F000; // 00000000000000001111000000000000
    int rt_shift = 12;
    inst.rt = get_bits(rt_shift, rt_mask, inst_code);

    // get the imm value
    int imm_mask = 0x00000FFF; // 00000000000000000000111111111111
    int imm_shift = 0;
    inst.imm = get_imm_bits(imm_shift, imm_mask, inst_code);

    // put the imm value in reg[1]
    reg[1] = inst.imm;

}

void clk(void) {
    if (ioreg[8] == 0xffffffff) { // check if clk reached max
        ioreg[8] = 0; // zero clk
    }
    else {
        ioreg[8] = ioreg[8] + 1; // increment clk
    }
}

void timer(void) {
    if (ioreg[12] == ioreg[13] && ioreg[0] == 1 && ioreg[11]) { // check if timer reached max value

        ioreg[3] = 1; // trigger irq0
        ioreg[12] = 0; // zero the timer

    }
    else if (ioreg[11]) { // check if timer is enabled

        if (timer_turn_on)
            timer_turn_on = 0;
        else
            ioreg[12] = ioreg[12] + 1; // increment the timer

    }
}

void interrupt(void) {

    // this is the condition from page 5 in the assignment
    if (((ioreg[0] && ioreg[3]) || (ioreg[1] && ioreg[4]) || (ioreg[2] && ioreg[5])) && !reti_flag) {
        reti_flag = 1; // signal that currently in interrupt handler
        ioreg[7] = pc; // save the return address in irqreturn
        pc = ioreg[6]; // jump to irqhandler

    }

}
