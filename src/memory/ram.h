#ifndef RAM_H
#define RAM_H

#define RAM_SIZE 0xFFF // 4096 bytes
#include "../chip8.h"
void Ram_match(Ram *Ram);
void Ram_init(Ram *Ram);
void Ram_set(Ram *Ram, int index, unsigned char value);
unsigned char Ram_get(Ram *Ram, int index);
#endif