#include <stdio.h>
#include "memory.h"
#include "bit_functions.h"


unsigned char memoryChip[32][32];

unsigned char mem_get(unsigned int row_selected, unsigned int col_selected) {
	return memoryChip[bit_find(row_selected)][bit_find(col_selected)];
}
void mem_put(unsigned int row_selected, unsigned int col_selected, unsigned char b) {
	memoryChip[bit_find(row_selected)][bit_find(col_selected)] = b;
}
void mem_dump() {
	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 32; j++) {
			printf("%c ", memoryChip[i][j]);
		}
		printf("\n");
	}
}
