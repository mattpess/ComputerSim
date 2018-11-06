#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bit_functions.h"
#include "decoder.h"
#include "memory_system.h"
#include "cpu.h"

int registers[16];
int cpsr = 0;
int reg, immediate, reg2, dest_reg;
unsigned int address;

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
	unsigned int inst = memory_fetch_word(registers[PC]);
	printf("Instruction: 0x%x\n", inst);
	//decode
	int opcode = inst >> 24;
	//execute
	switch (opcode) {
    case LDR:
		printf("LDR :: ");
        reg = inst >> 16 & 0xff;
        address = inst & 0xffff;
        if (address > 1023 || reg > 15) {
            printf("Address/Register out of bounds.\n");
            exit(1);
        }
        registers[reg] = memory_fetch_word(address);
        printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);
        registers[PC] += 4;
        break;
    case LDI:
		printf("LDI :: ");
		reg = inst >> 16 & 0xff;
		immediate = inst & 0xffff;
		if (reg > 15) {
			printf("Register out of bounds.\n");
			exit(1);
			}
		registers[reg] = immediate;
		printf("reg: %d, reg val: 0x%x08x, immediate: 0x%04x\n", reg, registers[reg], address);
		registers[PC] += 4;
		break;
	case LDX:
		printf("LDX\n");
		dest_reg = inst >> 16 & 0xff;
        reg2 = inst >> 8 & 0xff; //offset
        reg = inst & 0xff;
        if (dest_reg > 15 || reg > 15) {
            printf("Register out of bounds.\n");
            exit(1);
        }
        address = registers[reg];
        if (address + reg2 > 1023) {
            printf("Address out of bounds.\n");
            exit(1);
        }
        registers[dest_reg] = memory_fetch_word(address + reg2);
        registers[PC] += 4;
		break;
	case STR:
		printf("STR\n");
		reg = inst >> 16 & 0xff;
        address = inst & 0xffff;
        if (address > 1023 || reg > 15) {
            printf("Address/Register out of bounds.\n");
            exit(1);
        }
        memory_store_word(address, registers[reg]);
		break;
	case ADD:
		printf("ADD :: ");
		dest_reg = inst >> 16 & 0xff;
        reg = inst >> 8 & 0xff;
        reg2 = inst & 0xff;
        if (dest_reg > 15 || reg > 15 || reg2 > 15) {
            printf("One or more registers out of bounds.\n");
            exit(1);
        }
        registers[dest_reg] = registers[reg] + registers[reg2];
        printf("dest_reg: %d, reg1 value: 0x%x08x, reg2 value: 0x%x08x\n", dest_reg, registers[reg], registers[reg2]);
        registers[PC] += 4;
		break;
	case SUB:
		printf("SUB :: ");
		dest_reg = inst >> 16 & 0xff;
        reg = inst >> 8 & 0xff;
        reg2 = inst & 0xff;
        if (dest_reg > 15 || reg > 15 || reg2 > 15) {
            printf("One or more registers out of bounds.\n");
            exit(1);
        }
        registers[dest_reg] = registers[reg] - registers[reg2];
        printf("dest_reg: %d, reg1 value: 0x%x08x, reg2 value: 0x%x08x\n", reg, registers[reg], registers[reg2]);
        registers[PC] += 4;
		break;
	case MUL:
		printf("MUL :: ");
		dest_reg = inst >> 16 & 0xff;
        reg = inst >> 8 & 0xff;
        reg2 = inst & 0xff;
        if (dest_reg > 15 || reg > 15 || reg2 > 15) {
            printf("One or more registers out of bounds.\n");
            exit(1);
        }
        registers[dest_reg] = registers[reg] * registers[reg2];
        printf("dest_reg: %d, reg1 value: 0x%x08x, reg2 value: 0x%x08x\n", reg, registers[reg], registers[reg2]);
        registers[PC] += 4;
		break;
	case DIV:
		printf("DIV :: ");
		dest_reg = inst >> 16 & 0xff;
        reg = inst >> 8 & 0xff;
        reg2 = inst & 0xff;
        if (dest_reg > 15 || reg > 15 || reg2 > 15) {
            printf("One or more registers out of bounds.\n");
            exit(1);
        }
        registers[dest_reg] = registers[reg] / registers[reg2];
        printf("dest_reg: %d, reg1 value: 0x%x08x, reg2 value: 0x%x08x\n", reg, registers[reg], registers[reg2]);
        registers[PC] += 4;
		break;
	case CMP:
		printf("Compare");
		reg = inst >> 8 & 0xff;
		reg2 = inst & 0xff;
		if (reg > 15 || reg2 > 15) {
			printf("Register out of bounds.\n");
			exit(1);
			}
		if (registers[reg] == registers[reg2]) {
			bit_set(&cpsr, Z);
			bit_clear(&cpsr, LT);
			bit_clear(&cpsr, GT);
			printf(" equals :: 0x%x\n", cpsr);
		}
		else if (registers[reg] < registers[reg2]) { 
			bit_clear(&cpsr, Z);
			bit_set(&cpsr, LT);
			bit_clear(&cpsr, GT);
			printf(" equals :: 0x%x\n", cpsr);
		}
		else { 
			bit_clear(&cpsr, Z);
			bit_clear(&cpsr, LT);
			bit_set(&cpsr, GT);
			printf(" equals :: 0x%x\n", cpsr);
		}
		registers[PC] += 4;
		break;
	case B:
		printf("Branch");
		address = inst & 0xffffff;
		if (address > 1023) {
            printf("Address out of bounds.\n");
            exit(1);
        }
        printf(" to 0x%x\n", address);
		registers[PC] = address;
		break;
	case BEQ:
		printf("Branch");
		if (bit_test(cpsr, Z) == 1) {
			address = inst & 0xffffff;
			if (address > 1023) {
				printf("Address out of bounds.\n");
				exit(1);
			}
			printf(" to 0x%x\n", address);
			registers[PC] = address;
		}
		else {
			registers[PC] += 4;
		}
		break;
	case BNE:
		printf("Branch");
		if (bit_test(cpsr, Z) == 0) {
			address = inst & 0xffffff;
			if (address > 1023) {
				printf("Address out of bounds.\n");
				exit(1);
			}
			printf(" to 0x%x\n", address);
			registers[PC] = address;
		}
		else {
			registers[PC] += 4;
		}
		break;
	case BLT:
		printf("Branch");
		if (bit_test(cpsr, LT) == 1) {
			address = inst & 0xffffff;
			if (address > 1023) {
				printf("Address out of bounds.\n");
				exit(1);
			}
			printf(" to 0x%x\n", address);
			registers[PC] = address;
		}
		else {
			registers[PC] += 4;
		}
		break;
	case BGT:
		printf("Branch");
		if (bit_test(cpsr, GT) == 0) {
			address = inst & 0xffffff;
			if (address > 1023) {
				printf("Address out of bounds.\n");
				exit(1);
			}
			printf(" to 0x%x\n", address);
			registers[PC] = address;
		}
		else {
			registers[PC] += 4;
		}
		break;
	}
}
void step_n(int n) {
	while (n > 0) {
		step();
		n--;
	}
}
