#include "ram.h"
#include "../stack/stack.h"
#include "../timer/timer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

void Memory_match(Memory *Memory)
{
    Memory->memory = (unsigned char *)malloc(sizeof(unsigned char) * 4096);
    if (Memory->memory == NULL)
    {
        printf("\033[1;31m");
        printf("Error allocating memory\n");
        printf("\033[0m");
        exit(1);
    }
    Memory->set = Memory_set;
    Memory->get = Memory_get;
    Memory->init = Memory_init;
    Memory->Delay_timer = Timer_delay;
    Memory->Sound_timer = Timer_sound;

}

static void Memory_check(Memory *Memory, int index)
{
    assert(index >= 0 && index < MEMORY_SIZE);
}
void Memory_init(Memory *Memory)
{
        const char charactere[] = {
        0xf0, 0x90, 0x90, 0x90, 0xf0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xf0, 0x10, 0xf0, 0x80, 0xf0, // 2
        0xf0, 0x10, 0xf0, 0x10, 0xf0, // 3
        0x90, 0x90, 0xf0, 0x10, 0x10, // 4
        0xf0, 0x80, 0xf0, 0x10, 0xf0, // 5
        0xf0, 0x80, 0xf0, 0x90, 0xf0, // 6
        0xf0, 0x10, 0x20, 0x40, 0x40, // 7
        0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
        0xf0, 0x90, 0xf0, 0x10, 0xf0, // 9
        0xf0, 0x90, 0xf0, 0x90, 0x90, // A
        0xe0, 0x90, 0xe0, 0x90, 0xe0, // B
        0xf0, 0x80, 0x80, 0x80, 0xf0, // C
        0xe0, 0x90, 0x90, 0x90, 0xe0, // D
        0xf0, 0x80, 0xf0, 0x80, 0xf0, // E
        0xf0, 0x80, 0xf0, 0x80, 0x80  // F
    };

    memset(Memory->memory, 0, sizeof(Memory->memory));   
    memcpy(Memory->memory, charactere,sizeof(charactere)); 

    stack_init(&(Memory->stack));


}
void Memory_set(Memory *Memory, int index, unsigned char value)
{
 
    Memory_check(Memory, index);
    ((unsigned char *)Memory->memory)[index] = value;

    
}

unsigned char* Memory_get(Memory *Memory, int index, int length)
{
    Memory_check(Memory, index);
    char *str = (char *)malloc(sizeof(char) * length);
    if (str == NULL)
    {
        printf("\033[1;31m");
        printf("Error allocating memory\n");
        printf("\033[0m");
        exit(1);
    }
    memcpy(str, ((unsigned char *)Memory->memory) + index, length);
    return str;
}

void Memory_destroy(Memory *Memory)
{
    free(Memory->memory);
}