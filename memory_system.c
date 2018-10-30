#include "memory_system.h"
#include "memory.h"
#include "decoder.h"
#include <stdio.h>

unsigned int concat(unsigned int x, unsigned int y);
void memory_store(int address, unsigned char value) {
	int lowerhalf = address & 0x1f;
	int upperhalf = (address >> 5) & 0x1f;
	mem_put(decoder(lowerhalf), decoder(upperhalf), value);
	printf("0x%x - memory stored at %d, %d\n", value, lowerhalf, upperhalf);
}
unsigned char memory_fetch(int address) {
	int lowerhalf = address & 0x1f;
	int upperhalf = (address >> 5) & 0x1f;
	return mem_get(decoder(lowerhalf), decoder(upperhalf));
}
unsigned int memory_fetch_word(int address) {
	unsigned int fetchA = memory_fetch(address);
	unsigned int fetchB = memory_fetch(address + 1);
	unsigned int fetchC = memory_fetch(address + 2);
	unsigned int fetchD = memory_fetch(address + 3);
	
	printf("0x%x 0x%x 0x%x 0x%x\n", fetchA, fetchB, fetchC, fetchD);
	
	//concatonate
	fetchA = concat(fetchA, fetchB);
	fetchC = concat(fetchC, fetchD);
	return concat(fetchA, fetchC);
	
}
void memory_dump(int start_address, int num_bytes) {
	for(int i = 0; i < num_bytes; i++) {
		printf("%c ", memory_fetch(start_address + i));
	}
}
void memory_store_word(int address, unsigned int value) {
	//Ask Gusty about splitting value into 4 parts
	unsigned char b1, b2, b3, b4;
	b1 = value & 0xff;
	b2 = value >> 8 & 0xff;
	b3 = value >> 16 & 0xff;
	b4 = value >> 24 & 0xff;
	printf("0x%x 0x%x 0x%x 0x%x\n", b1, b2 , b3, b4);
	memory_store(address, b1);
	memory_store(address+2, b2);
	memory_store(address+4, b3);
	memory_store(address+6, b4);
}
void load_memory(char *filename){
	
	FILE *fp = fopen(filename, "r");
	unsigned int i; 
	fscanf(fp, "%d", i);
	unsigned int tempData;
	while(fscanf(fp, "%d", tempData) != EOF) {
		memory_store_word(i, tempData);
		i++;
	}	
}
unsigned int concat(unsigned int x, unsigned int y){
	unsigned int i = 10;
	while(y >= i)
		i *= 10;
	return (unsigned int)(x * i + y);
}
