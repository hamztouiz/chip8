#ifndef STACK_H
#define STACK_H

#include "../chip8.h"
void stack_init(Stack *stack);
unsigned short stack_pop(Stack *stack);
void stack_push(Stack *stack, unsigned short value);
#endif