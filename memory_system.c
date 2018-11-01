#include "memory_system.h"
#include "memory.h"
#include "decoder.h"
#include <stdio.h>

//unsigned int concat(unsigned int x, unsigned int y);
void memory_store(int address, unsigned char value) {
	int lowerhalf = address & 0x1f;
	int upperhalf = (address >> 5) & 0x1f;
	mem_put(decoder(upperhalf), decoder(lowerhalf), value);
	printf("0x%x - memory stored at %d, %d\n", value, lowerhalf, upperhalf);
}
unsigned char memory_fetch(int address) {
	int lowerhalf = address & 0x1f;
	int upperhalf = (address >> 5) & 0x1f;
	return mem_get(decoder(upperhalf), decoder(lowerhalf));
}
unsigned int memory_fetch_word(int address) {
	unsigned char b1 = memory_fetch(address);
	unsigned char b2 = memory_fetch(address + 1);
	unsigned char b3 = memory_fetch(address + 2);
	unsigned char b4 = memory_fetch(address + 3);
	
	printf("0x%x 0x%x 0x%x 0x%x\n", b1, b2, b3, b4);
	
	//concatonate
	/*
	b1 = concat(b1, b2);
	b3 = concat(b3, b4);
	return concat(b1, b3);
	*/
	return b4<<24 | b3<<16 | b2<<8 | b1;
	
}
void memory_dump(int start_address, int num_bytes) {
	for(int i = 0; i < num_bytes; i++) {
		printf("0x%x ", memory_fetch(start_address + i));
	}
	printf("\n");
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
	memory_store(address+1, b2); // address+1
	memory_store(address+2, b3); // address+2
	memory_store(address+3, b4); // address+3
}
void load_memory(char *filename){
	FILE *fp = fopen(filename, "r");
	int i; 
	fscanf(fp, "%d", &i);
	unsigned int tempData;
	int count = 0;
	while(fscanf(fp, "%x", &tempData) != EOF && count < 25) { //check infinite loop later
		memory_store_word(i, tempData);
		i = i+4;
		count++;
	}	
	fclose(fp);
}
/*unsigned int concat(unsigned int x, unsigned int y){
	unsigned int i = 10;
	while(y >= i)
		i *= 10;
	return (unsigned int)(x * i + y);
}*/
