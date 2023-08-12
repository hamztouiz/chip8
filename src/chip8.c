#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "display/display.h"
#include "memory/ram/ram.h"

Display chip8_display;
Memory chip8_Memory;

void main()
{

    display_match(&chip8_display);
    Memory_match(&chip8_Memory);

    chip8_display.init(&chip8_display);
    chip8_Memory.init(&chip8_Memory);

    chip8_display.destroy(&chip8_display);
    exit(0);
}

