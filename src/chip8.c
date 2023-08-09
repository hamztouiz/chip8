#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "display/display.h"
#include "memory/ram.h"
#define IFDEBUG(char) \
    if (DEBUG)        \
        printf("DEBUG: %s:%d: %s\n", __FILE__, __LINE__, char);

Display chip8_display;
Ram chip8_Ram;

void main()
{

    display_match(&chip8_display);
    Ram_match(&chip8_Ram);

    chip8_display.init(&chip8_display);
    chip8_Ram.init(&chip8_Ram);

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                goto quit;
        }
    }
quit:
    chip8_display.destroy(&chip8_display);
    exit(0);
}
