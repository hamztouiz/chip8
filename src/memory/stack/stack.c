#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void stack_init(Stack *stack)
{
    stack->SP = 0;
    for (int i = 0; i < 16; i++)
    {
        stack->stack[i] = 0;
    }
    stack->pop = stack_pop;
    stack->push = stack_push;
    IFDEBUG("Initialized stack");

}
unsigned short stack_pop(Stack *stack)
{
    if (stack->SP == 0 || stack->SP > 16 || stack->stack[stack->SP-1] == 0)
    {
        //print in red
        printf("\033[1;31m");
        printf("Error: Stack underflow\n");
        printf("\033[0m");
        exit(1);
    }
    return stack->stack[--stack->SP];
}

void stack_push(Stack *stack, unsigned short value)
{
    if (stack->SP == 16)
    {
        printf("\033[1;31m");
        printf("Error: Stack overflow\n");
        printf("\033[0m");
        exit(1);
    }
    stack->stack[stack->SP++] = value;
}
