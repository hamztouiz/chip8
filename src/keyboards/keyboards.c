#include "keyboards.h"
#include <SDL2/SDL.h>
#include "../chip8.h"

static void keyboard_down(Keyboard *keyboard, SDL_Keycode key);
static void keyboard_up(Keyboard *keyboard, SDL_Keycode key);

void keyboard_match(Keyboard *keyboard)
{
    IFDEBUG("Initializing keyboard");
    keyboard->event = keyboard_event;
    keyboard->destroy = keyboard_destroy;
}

char keyboard_event(Keyboard *keyboard)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        IFDEBUG("Event polled");

        if (event.type == SDL_QUIT)
        {
            IFDEBUG("Quitting");
            exit(0);
        }
        
        if (event.type == SDL_QUIT)
            break;
        if (event.type == SDL_KEYDOWN)
        {
            keyboard_down(keyboard, event.key.keysym.sym);
            IFDEBUG("Key pressed");
        }
        else if (event.type == SDL_KEYUP)
        {
            keyboard_up(keyboard, event.key.keysym.sym);
            IFDEBUG("Key released");
        }
    }
    return event.key.keysym.sym;   

}
static void keyboard_up(Keyboard *keyboard, SDL_Keycode key)
{
    uint8_t i;
    for (i = 0; i < KEYBOARD_SIZE; i++)
        if (keyboard->maps[i] == key)
            break;
    if (i == KEYBOARD_SIZE)
    {
        printf("\033[1;31m");
        printf("Error: Key not found\n");
        printf("\033[0m");
        return;
    }
    keyboard->keys[i] = 0;
}

static void keyboard_down(Keyboard *keyboard, SDL_Keycode key)
{
    uint8_t i;
    for (i = 0; i < KEYBOARD_SIZE; i++)
        if (keyboard->maps[i] == key)
            break;
    if (i == KEYBOARD_SIZE)
    {
        printf("\033[1;31m");
        printf("Error: Key not found\n");
        printf("\033[0m");
        return;
    }
    keyboard->keys[i] = 1;    
}

void keyboard_destroy(Keyboard *keyboard)
{
}