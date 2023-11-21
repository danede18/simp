#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "global_vars.h"
#include "file_utils.h"

int open_file(char* filename, char* op) {
    curr_file = fopen(filename, op);
    if (curr_file == NULL) {
        printf("Error: Unable to open file %s.\n", filename);
        fclose(curr_file);
        return 1;
    }
    return 0;
}

int write_output_files(char* regout_file, char* memout_file, char* cycles_file) {

    //cycles
    if (open_file(cycles_file, "w")) {
        return 1;
    }
    fprintf(curr_file, "%d\n", cycles);
    fclose(curr_file);

    //Memout
    if (open_file(memout_file, "w")) {
        return 1;
    }
    for (int i = 0; i < 512; i++)
    {
        fprintf(curr_file, "%08X\n", mem[i]);
    }
    fclose(curr_file);

    //Regout
    if (open_file(regout_file, "w")) {
        return 1;
    }
    for (int i = 2; i < 16; i++)
    {
        fprintf(curr_file, "%08X\n", reg[i]);
    }
    fclose(curr_file);

    return 0;
}

void append_trace(void) {
    fprintf(curr_file, "%08X ", pc);
    fprintf(curr_file, "%08X ", inst_code);
    for (int i = 0; i < 15; i++)
    {
        fprintf(curr_file, "%08X ", reg[i]);
    }
    fprintf(curr_file, "%08X\n", reg[15]);
}

void load_mem() {
    // load the memin.txt to the mem array

    char str[10];
    int i = 0;

    while (fgets(str, 10, curr_file) != NULL) {
        // read each line in the file and convert to int to put in the mem array    
        mem[i] = (int)strtoul(str, NULL, 16);
        i++;
    }

    for (i; i < 512; i++) {
        // fill rest of memory with zeros.
        mem[i] = 0;
    }

}


void init() {
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
    load_mem(curr_file);


}