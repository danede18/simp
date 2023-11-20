#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "global_vars.h"
#include "sim_utils.h"

void intToHexCharArray(int num, char* hexArray) { //takes an integer and makes a hexadecimal representation
    sprintf(hexArray, "%08X", num);
    int length = strlen(hexArray);
    for (int i = 0; i < length; i++) {
        if (hexArray[i] >= 'a' && hexArray[i] <= 'f') { //makes the small letters into a big one
            hexArray[i] = hexArray[i] - 32;
        }
    }
}

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


void load_mem(FILE* file) {
    // load the memin.txt to the mem array

    char str[10];
    int i = 0;

    while (fgets(str, 10, file) != NULL) {
        // read each line in the file and convert to int to put in the mem array    
        mem[i] = (int)strtoul(str, NULL, 16);
        i++;
    }

    for (i; i < 512; i++) {
        // fill rest of memory with zeros.
        mem[i] = 0;
    }


}


void init(FILE* file) {
    // set the initial value of regs
    for (int i = 0; i < 16; i++)
    {
        reg[i] = 0;
    }
    for (int i = 0; i < 14; i++)
    {
        ioreg[i] = 0;
    }
    // set the initial value of PC
    pc = 0;
    // set the initial value of reti_flag
    reti_flag = 0;
    // load the memin file to the memory
    load_mem(file);


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
