#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include "chip8.h"
#include "display/display.h"
#include "memory/ram/ram.h"
#include "keyboards/keyboards.h"
#include <unistd.h>
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

    pthread_t thread_id, thread_id2, thread_id3;
    pthread_create(&thread_id, NULL, chip8_keyboard.event, NULL);

    printf("### SETTING MEMORY ###\n");
    chip8_Memory.set(&chip8_Memory, 0x201, 1);
    printf("Set memory at index 0 to 1\n");
    printf("### SETTING MEMORY ###\n \n");

    printf("### GETTING MEMORY ###\n");
    unsigned char *test_memory = chip8_Memory.get(chip8_Memory, 0, 0);
    printf("Memory at index 0 is %d\n", *test_memory);
    printf("### GETTING MEMORY ###\n \n");

    printf("### GETTING MEMORY ###\n");
    test_memory = chip8_Memory.get(chip8_Memory, 4095, 0);
    printf("Memory at index 4095 is %d\n", *test_memory);
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
    unsigned char *sprite = chip8_Memory.get(chip8_Memory, 5*10, 5);
    chip8_display.drawSprite(&chip8_display, 32, 16, sprite, 5);
    chip8_display.drawSprite(&chip8_display, 63, 31, sprite, 5);
    chip8_display.print(&chip8_display);
    printf("Press any key to continue\n");
    pthread_create(&thread_id, NULL, chip8_Memory.Sound_timer, NULL);
    usleep(4000000);

    printf("### SETTING DELAY TIMER ###\n");
    chip8_Memory.delay_timer = 255;
    chip8_Memory.sound_timer = 255;
    chip8_keyboard.keyboard_get_is_change(&chip8_keyboard);

    


}
