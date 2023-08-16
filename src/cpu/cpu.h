#ifndef CPU_H
#define CPU_H
#include "../chip8.h"   
#define CLS 0x00E0 
#define RET 0x00EE
#define JP 0x1000
#define CALL 0x2000

void cpu_match(CPU * cpu);
unsigned char* cpu_fetch(CPU* cpu, Memory* memory);
unsigned char* cpu_decode(CPU* cpu , unsigned char *instruction);
void cpu_execute(CPU* cpu, Memory* memory, Display* display, Keyboard* keyboard, unsigned char * niblle, unsigned char *instruction);

#endif