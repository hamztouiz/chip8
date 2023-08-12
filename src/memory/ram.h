#ifndef RAM_H
#define RAM_H

#define MEMORY_SIZE 0x1000 // 4096 bytes
#include "../chip8.h"
void Memory_match(Memory *Memory);
void Memory_init(Memory *Memory);
void Memory_set(Memory *Memory, int index, unsigned char value);
unsigned char Memory_get(Memory *Memory, int index);
#endif