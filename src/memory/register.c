#include "register.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void static check_register_index(unsigned char register_index)
{
    assert (register_index < 15 || register_index >= 0);
}

unsigned char get_register_value(Memory *Memory, unsigned char register_index)
{
    check_register_index(register_index);
    return Memory->registersVX[register_index];
}
void set_register_value(Memory *Memory, unsigned char register_index, unsigned char value)
{
    check_register_index(register_index);
    Memory->registersVX[register_index] = value;
}

void set_I_value(Memory *Memory, unsigned short value)
{
    Memory->I = value;
}

unsigned short get_I_value(Memory *Memory)
{
    if(Memory->I == 0)
    {
        printf("I is 0\n");
        exit(1);
    }
    return Memory->I;
}