#ifndef RAM_H
#define RAM_H

#define RAM_SIZE 0xFFF // 4096 bytes
#include "../chip8.h"
void ram_match(ram *ram);
void ram_init(ram *ram);
void ram_set(ram *ram, int index, unsigned char value);
unsigned char ram_get(ram *ram, int index);
#endif