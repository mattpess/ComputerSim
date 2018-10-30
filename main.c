#include <stdio.h>
#include "memory.h"
#include "memory_system.h"

int main() {
	
	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 32; j++) {
			memoryChip[i][j] = '0';
		}
	}
	
	printf("Memory at 0,0: %c\n", memory_fetch(0000000000));
	
	//mem_put(0, 0, '7');
	memory_store(0000000000, 'A');
	
	printf("Memory at 0,0: %c\n", memory_fetch(0000000000));
	
	memory_store_word(0000000000, 0x00000001);
	
	printf("Memory at 0,0: 0x%x\n", memory_fetch_word(0000000000));
	
	memory_dump(0, 20);
	printf("\n");
	
	return 0;
}
