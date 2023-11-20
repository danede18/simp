#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "global_vars.h"
#include "execute.h"
#include "sim_utils.h"


int main(int argc, char* argv[]) {


    if (argc != 6) {																	// Check whether command arguments were given properly
        printf("ERROR - argc = %0d, missing arguments.", argc);
        return 1;
    }

    // check and open the memin file.
    FILE* memin_file;
    memin_file = fopen(argv[1], "r");
    if (NULL == memin_file) {
        printf("Error: Unable to open file %s.\n", argv[1]);
        return 1;
    }



    // initialize the registers and memory
    init(memin_file);

    fclose(memin_file);

    int cycles = 1; //measure the cycles
    int i;
    char hexArray[9];//makes the hexadecimal representaiton of the integer

    //Trace
    FILE* trace_file;   //open the trace file
    trace_file = fopen(argv[4], "w");
    if (trace_file == NULL) {
        printf("Error: Unable to open file %s.\n", argv[4]);
        return 1;
    }

    while (1) {
        
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
        


        // this is the condition from page 5 in the assignment
        if (((ioreg[0] && ioreg[3]) || (ioreg[1] && ioreg[4]) || (ioreg[2] && ioreg[5])) && !reti_flag) {
            reti_flag = 1; // signal that currently in interrupt handler
            ioreg[7] = pc; // save the return address in irqreturn
            pc = ioreg[6]; // jump to irqhandler
            
        }


        // perform instructions until a halt instruction is reached

        fetch(); // fetch the next instruction from memory
        decode(); // decode the instruction

        intToHexCharArray(pc, hexArray); //print the arguments to file trace 
        fprintf(trace_file, "%s ", hexArray);   //print the arguments to file trace 
        intToHexCharArray(inst_code, hexArray); //print the arguments to file trace 
        fprintf(trace_file, "%s ", hexArray);   //print the arguments to file trace 
        for (i = 0; i < 15; i++)
        {

            intToHexCharArray(reg[i], hexArray);    //print the arguments to file trace 
            fprintf(trace_file, "%s ", hexArray);   //print the arguments to file trace 
        }
        intToHexCharArray(reg[15], hexArray);   //print the arguments to file trace 
        fprintf(trace_file, "%s\n", hexArray);  //print the arguments to file trace 



        if (inst.opcode == 19) {
            // if the instruction is halt, then halt...
            break;

        }
        else {
            // execute the instruction
            execute();
            if (ioreg[8] == 0xffffffff) { // check if clk reached max
                ioreg[8] = 0; // zero clk
            }
            else {
                ioreg[8] = ioreg[8] + 1; // increment clk
            }
        }
        cycles++;

    }


    //cycles

    FILE* cycle_file;
    cycle_file = fopen(argv[5], "w"); //print the cycles into the cycles file
    if (cycle_file == NULL) {
        printf("Error: Unable to open file %s.\n", argv[5]);
        return 1;
    }
    fprintf(cycle_file, "%d\n", cycles);
    fclose(cycle_file);

    //Memout
    FILE* memout_file;
    memout_file = fopen(argv[2], "w"); //print the memory to the file memout
    if (memout_file == NULL) {
        printf("Error: Unable to open file %s.\n", argv[2]);
        return 1;
    }
    for (i = 0; i < 512; i++)
    {
        intToHexCharArray(mem[i], hexArray);
        fprintf(memout_file, "%s\n", hexArray);
    }
    fclose(memout_file);

    //Regout
    FILE* reg_file;
    reg_file = fopen(argv[3], "w"); //print the register to the file Regout
    if (reg == NULL) {
        printf("Error: Unable to open file %s.\n", argv[3]);
        return 1;
    }
    for (i = 2; i < 16; i++)
    {
        intToHexCharArray(reg[i], hexArray);
        fprintf(reg_file, "%s\n", hexArray);
    }
    fclose(reg_file);

    return 0;

}