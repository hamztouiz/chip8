#include "ram.h"
#include <stdlib.h>
#include <string.h>

void Memory_match(Memory *Memory)
{
    Memory->memory = (unsigned char *)malloc(sizeof(unsigned char) * 4096);
    Memory->set = Memory_set;
    Memory->get = Memory_get;
    Memory->init = Memory_init;
}
void Memory_init(Memory *Memory)
{
    memset(Memory->memory, 0, sizeof(Memory->memory));
}
void Memory_set(Memory *Memory, int index, unsigned char value)
{
    ((unsigned char *)Memory->memory)[index] = value;
}

unsigned char Memory_get(Memory *Memory, int index)
{

    return ((unsigned char *)Memory->memory)[index];
}