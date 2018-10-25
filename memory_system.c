#include "memory_system.h"
#include "memory.h"
#include "decoder.h"
#include <stdio.h>

void memory_store(int address, unsigned char value) {
	int lowerhalf = address & 0x1f;
	int upperhalf = (address >> 5) & 0x1f;
	mem_put(decoder(lowerhalf), decoder(upperhalf), value);
	printf("memory stored at %d, %d\n", lowerhalf, upperhalf);
}
unsigned char memory_fetch(int address) {
	int lowerhalf = address & 0x1f;
	int upperhalf = (address >> 5) & 0x1f;
	return mem_get(decoder(lowerhalf), decoder(upperhalf));
}
unsigned int memory_fetch_word(int address) {
	int fetchA = memory_fetch(address);
	int fetchB = memory_fetch(address + 1);
	int fetchC = memory_fetch(address + 2);
	int fetchD = memory_fetch(address + 3);
	//concatonate
}
void memory_dump(int start_address, int num_bytes) {
	for(int i = 0; i < num_bytes; i++) {
		
	}
}
void memory_store_word(int address, unsigned int value);
void load_memory(char *filename);
