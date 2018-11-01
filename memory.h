extern unsigned char memoryChip[32][32];
unsigned char mem_get(unsigned int row_selected, unsigned int col_selected);
void mem_put(unsigned int row_selected, unsigned int col_selected, unsigned char b);
void mem_dump();
void memory_fill(unsigned char value);
