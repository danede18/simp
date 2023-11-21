#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "global_vars.h"
#include "execute.h"
#include "sim_utils.h"
#include "file_utils.h"


int main(int argc, char* argv[]) {


    if (argc != 6) {																	// Check whether command arguments were given properly
        printf("ERROR - argc = %0d, missing arguments.", argc);
        return 1;
    }

    // check and open the memin file.
    if (open_file(argv[1], "r")) {
        return 1;
    }

    // initialize the registers and memory
    init();

    fclose(curr_file);

    cycles = 1; //measure the cycles

    //Trace
    if (open_file(argv[4], "w")) {
        return 1;
    }


    while (1) {

        timer();
      
        interrupt();

        // perform instructions until a halt instruction is reached

        fetch(); // fetch the next instruction from memory
        decode(); // decode the instruction

        append_trace();

        if (execute() == 19) {
            // if the instruction is halt, then halt...
            break;

        }

        clk();

        cycles++;

    }

    fclose(curr_file);

    return write_output_files(argv[3], argv[2], argv[5]);

}