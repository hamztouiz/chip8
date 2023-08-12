#ifndef CPU_H
#define CPU_H
#include "../chip8.h"   


void cpu_match(CPU * cpu);
void cpu_init(CPU* cpu);
void cpu_execute(CPU* cpu);

#endif