#include "global_vars.h"
#include "execute.h"


// for each function perform the operation of the opcode and increment the PC appropriately

int execute(void) {

    // execute the instruction

    switch (inst.opcode)
    { // call the function to perform according to the opcode
    case 0:
        add();
        break;

    case 1:
        sub();
        break;

    case 2:
        and ();
        break;

    case 3:
        or ();
        break;

    case 4:
        sll();
        break;

    case 5:
        sra();
        break;

    case 6:
        srl();
        break;

    case 7:
        beq();
        break;

    case 8:
        bne();
        break;

    case 9:
        blt();
        break;

    case 10:
        bgt();
        break;

    case 11:
        ble();
        break;

    case 12:
        bge();
        break;

    case 13:
        jal();
        break;

    case 14:
        lw();
        break;

    case 15:
        sw();
        break;

	case 16:
		reti();
		break;

	case 17:
		in();
		break;

	case 18:
		out();
		break;

    case 19:
        halt();
        break;

    default:
        break;
    }


	reg[0] = 0;

	return inst.opcode;
}


void add(void) {
	
	reg[inst.rd] = reg[inst.rs] + reg[inst.rt];
	pc = pc + 1;

}

void sub(void) {
	
	reg[inst.rd] = reg[inst.rs] - reg[inst.rt];
	pc = pc + 1;

}

void and (void) {
	
	reg[inst.rd] = reg[inst.rs] & reg[inst.rt];
	pc = pc + 1;

}

void or (void) {

	reg[inst.rd] = reg[inst.rs] | reg[inst.rt];
	pc = pc + 1;

}

void sll(void) {

	reg[inst.rd] = reg[inst.rs] << reg[inst.rt];
	pc = pc + 1;

}

void sra(void) {

	reg[inst.rd] = reg[inst.rs] >> reg[inst.rt];
	pc = pc + 1;

}

void srl(void) {
	// use unsinged int to perform logical right shift
	unsigned int num = (unsigned int)reg[inst.rs];
	reg[inst.rd] = num >> reg[inst.rt];
	pc = pc + 1;

}


// for branch operations branch if condition is met and increment PC only if condition isn't met.
void beq(void) {

	if (reg[inst.rs] == reg[inst.rt]) {
		pc = reg[inst.rd];
	}
	else {
		pc = pc + 1;
	}

}

void bne(void) {

	if (reg[inst.rs] != reg[inst.rt]) {
		pc = reg[inst.rd];
	}
	else {
		pc = pc + 1;
	}
}

void blt(void) {

	if (reg[inst.rs] < reg[inst.rt]) {
		pc = reg[inst.rd];
	}
	else {
		pc = pc + 1;
	}
}

void bgt(void) {

	if (reg[inst.rs] > reg[inst.rt]) {
		pc = reg[inst.rd];
	}
	else {
		pc = pc + 1;
	}
}

void ble(void) {

	if (reg[inst.rs] <= reg[inst.rt]) {
		pc = reg[inst.rd];
	}
	else {
		pc = pc + 1;
	}
}

void bge(void) {

	if (reg[inst.rs] >= reg[inst.rt]) {
		pc = reg[inst.rd];
	}
	else {
		pc = pc + 1;
	}
}


void jal(void) {
	// save PC+1 in the $ra register and jump to the register rd
	reg[15] = pc + 1;
	pc = reg[inst.rd];

}

// load and save word oprations write in the mem array
void lw(void) {

	reg[inst.rd] = mem[reg[inst.rs] + reg[inst.rt]];
	pc = pc + 1;

}

void sw(void) {

	mem[reg[inst.rs] + reg[inst.rt]] = reg[inst.rd];
	pc = pc + 1;

}


void reti(void) {

	pc = ioreg[7];
	reti_flag = 0;

}

void in(void) {

	reg[inst.rd] = ioreg[reg[inst.rs] + reg[inst.rt]];
	pc = pc + 1;

}

void out(void) {

	if ((reg[inst.rs] + reg[inst.rt]) == 11 && reg[inst.rd] && !ioreg[11])
		timer_turn_on = 1;

	ioreg[reg[inst.rs] + reg[inst.rt]] = reg[inst.rd];
	pc = pc + 1;

}

void halt(void) {}