#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chip8.h"
#include "display/display.h"
#define IFDEBUG(char) \
    if (DEBUG)        \
        printf("DEBUG: %s:%d: %s\n", __FILE__, __LINE__, char);

Display chip8_display;

void main()
{

    display_match(&chip8_display);
    chip8_display.init(&chip8_display);
}
