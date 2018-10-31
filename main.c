#include <stdio.h>
#include "memory.h"
#include "memory_system.h"

int main() {
	
	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 32; j++) {
			memoryChip[i][j] = 0;
		}
	}
	
	printf("Memory at 0,0: %c = 0x%x\n", memory_fetch_word(0));
	
	memory_store_word(0, (0x6968));
	
	printf("Memory at 0,0: %c = 0x%x\n", memory_fetch_word(0));
	
	memory_store_word(4, (0x796568));
	
	printf("Memory at 0,4: %c = 0x%x\n", memory_fetch_word(4));
	
	
	/*printf("Memory at 0,0: %c = 0x%x\n", memory_fetch(0), memory_fetch(0));
	printf("Memory at 0,1: %c = 0x%x\n", memory_fetch(1), memory_fetch(1));
	printf("Memory at 0,2: %c = 0x%x\n", memory_fetch(2), memory_fetch(2));
	printf("Memory at 0,3: %c = 0x%x\n", memory_fetch(3), memory_fetch(3));
	printf("Memory Word:   %c or %d = 0x%x\n", memory_fetch_word(0), memory_fetch_word(0), memory_fetch_word(0));
	
	memory_dump(0, 8);
	printf("\n");
	
	mem_put(0, 1, 0);
	printf("mem_put at 1: %c = 0x%x\n", mem_get(0, 1), mem_get(0, 1));
	mem_put(0, 3, 0);
	printf("mem_put at 3: %c = 0x%x\n", mem_get(0, 3), mem_get(0, 3));
	
	printf("Memory at 0,0: %c = 0x%x\n", memory_fetch(0), memory_fetch(0));
	printf("Memory at 0,1: %c = 0x%x\n", memory_fetch(1), memory_fetch(1));
	printf("Memory at 0,2: %c = 0x%x\n", memory_fetch(2), memory_fetch(2));
	printf("Memory at 0,3: %c = 0x%x\n", memory_fetch(3), memory_fetch(3));
	printf("Memory Word:   %c or %d = 0x%x\n", memory_fetch_word(0), memory_fetch_word(0), memory_fetch_word(0));
	
	printf("mem_get at 1: %c = 0x%x\n", mem_get(0, 1), mem_get(0, 1));
	printf("mem_get at 3: %c = 0x%x\n", mem_get(0, 3), mem_get(0, 3));*/
	
	printf("memory_dump 0-8:\n");
	memory_dump(0, 20);
	printf("\n");
	
	return 0;
}
