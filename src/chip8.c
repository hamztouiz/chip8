#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <unistd.h>
#include <pthread.h>

#include "chip8.h"
#include "display/display.h"
#include "memory/ram/ram.h"
#include "keyboards/keyboards.h"
#include "cpu/cpu.h"

Display chip8_display;
Memory chip8_Memory;
Keyboard chip8_keyboard;
CPU chip8_cpu;


void main()
{

    //open file and read it
    FILE *file = fopen("/home/hamzux/projet/chip8/media/roms/INVADERS", "rb");
    if (file == NULL)
    {
        printf("Error: Couldn't open file\n");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char *buffer = malloc(file_size);
    fread(buffer, file_size, 1, file);
    fclose(file);

    Memory_match(&chip8_Memory);
    chip8_Memory.init(&chip8_Memory);


    keyboard_match(&chip8_keyboard);
    chip8_keyboard.maps = "1234PROrqsdfwxcv";

    display_match(&chip8_display);
    chip8_display.init(&chip8_display);

    cpu_match(&chip8_cpu);

    for (int i = 0; i < file_size; i++)    
    {
        chip8_Memory.set(&chip8_Memory, 0x200 + i, buffer[i]); 
    }

    free(buffer);
    pthread_t thread_id, thread_id2, thread_id3;
    pthread_create(&thread_id2, NULL, chip8_Memory.Delay_timer, NULL);
    pthread_create(&thread_id3, NULL, chip8_Memory.Sound_timer, NULL);

    while (1)
    {
 
        unsigned char *instruction = chip8_cpu.fetch(&chip8_cpu, &chip8_Memory);
        unsigned char *niblle = chip8_cpu.decode(&chip8_cpu, instruction);
        chip8_keyboard.event(&chip8_keyboard);
        chip8_cpu.execute(&chip8_cpu, &chip8_Memory, &chip8_display, &chip8_keyboard, niblle, instruction);
        free(niblle);
    }
    
    exit(0);
}

