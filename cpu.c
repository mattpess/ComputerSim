#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decoder.h"
#include "cpu.h"

int registers[16];
int cpsr = 0;


void set_reg(int reg, int value) {
	registers[reg] = value;
}
int get_reg(int reg) {
	return registers[reg];
}
int get_cpsr() {
	return cpsr;
}
void show_regs() {
	for(int i = 0; i < 16; i++) {
		printf("REG %d: 0x%x\n", i, registers[i]);
	}
	printf("\n");
}
void step() {
	//fetch
	unsigned int inst = registers[PC];
	//decode
	int opcode = inst >> 24;
	//execute
	switch (opcode) {
    case LDR:
        reg = inst >> 16 & 0xff;
        address = inst & 0xffff;
        if (address > 1023 || reg > 15) {
            printf("Address/Register out of bounds.\n");
            exit(1);
        }
        registers[reg] = memory_fetch_word(address);
        printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
        pc += 4;
        break;
    case LDI:
		reg = inst >> 16 & 0xff;
		immediate = inst & 0xffff;
		if (reg > 15) {
			printf("Register out of bounds.\n");
			exit(1);
			}
		registers[reg] = immediate;
		printf("reg: %d, reg val: 0x%x08x, immediate: 0x%04x\n", reg, registers[reg], address);
		pc += 4;
		break;
	case LDX:
		break;
	case STR:
		break;
	case ADD:
		break;
	case SUB:
		break;
	case MUL:
		break;
	case DIV:
		break;
	case CMP:
		break;
	case B:
		break;
	case BEQ:
		break;
	case BNE:
		break;
	case BLT:
		break;
	case BGT:
		break;
	}
}
void step_n(int n) {
	
}
