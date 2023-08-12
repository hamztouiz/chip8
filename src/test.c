#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "display/display.h"
#include "memory/ram.h"
#include "keyboards/keyboards.h"
#define IFDEBUG(char) \
    if (DEBUG)        \
        printf("DEBUG: %s:%d: %s\n", __FILE__, __LINE__, char);

Display chip8_display;
Memory chip8_Memory;
Keyboard chip8_keyboard;

void main()
{

    Memory_match(&chip8_Memory);
    chip8_Memory.init(&chip8_Memory);

    keyboard_match(&chip8_keyboard);
    chip8_keyboard.maps = "1234azerqsdfwxcv";

    display_match(&chip8_display);
    chip8_display.init(&chip8_display);

    printf("### SETTING MEMORY ###\n");
    chip8_Memory.set(&chip8_Memory, 0, 1);
    printf("Set memory at index 0 to 1\n");
    printf("### SETTING MEMORY ###\n \n");

    printf("### GETTING MEMORY ###\n");
    unsigned char test_memory = chip8_Memory.get(&chip8_Memory, 0);
    printf("Memory at index 0 is %d\n", test_memory);
    printf("### GETTING MEMORY ###\n \n");

    printf("### GETTING MEMORY ###\n");
    test_memory = chip8_Memory.get(&chip8_Memory, 4095);
    printf("Memory at index 4095 is %d\n", test_memory);
    printf("### GETTING MEMORY ###\n \n");

    for (int i = 0; i < 16; i++)
    {
        printf("### PUSHING TO STACK ###\n");
        chip8_Memory.stack.push(&chip8_Memory.stack, i+1);
        printf("Pushed %d to stack\n", i+1);
        printf("### PUSHING TO STACK ###\n \n");
    }

    for (int i = 0; i < 16; i++)
    {
        printf("### POPPING FROM STACK ###\n");
        unsigned short popped = chip8_Memory.stack.pop(&chip8_Memory.stack);
        printf("Popped %d from stack\n", popped);
        printf("### POPPING FROM STACK ###\n \n");
    }
      
// test registerVX
    for (int i = 0; i < 16; i++)
    {
        printf("### SETTING REGISTERVX ###\n");
        chip8_Memory.registersVX[i] = i;
        printf("Set registerVX at index %d to %d\n", i, i);
        printf("### SETTING REGISTERVX ###\n \n");
    }

    for (int i = 0; i < 16; i++)
    {
        printf("### GETTING REGISTERVX ###\n");
        unsigned char test_registerVX = chip8_Memory.registersVX[i];
        printf("registerVX at index %d is %d\n", i, test_registerVX);
        printf("### GETTING REGISTERVX ###\n \n");
    }
    // wait press key
    printf("Press any key to continue\n");
    while (chip8_keyboard.event(&chip8_keyboard) != '0')
    {
        continue;
    }

    


}