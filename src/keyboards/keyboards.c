#include "keyboards.h"
#include <SDL2/SDL.h>
#include "../chip8.h"

static void keyboard_down( SDL_Keycode key);
static void keyboard_up(SDL_Keycode key);
extern Keyboard chip8_keyboard;

void keyboard_match(Keyboard *keyboard)
{
    IFDEBUG("Initializing keyboard");
    keyboard->event = keyboard_event;
    keyboard->destroy = keyboard_destroy;
    keyboard->get = keyboard_get;
    keyboard->keyboard_get_is_change = keyboard_get_is_change;

}

void *keyboard_event()
{
    SDL_Event event;
    IFDEBUG("Event polled");
        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_QUIT)
            {
                IFDEBUG("Quitting");
                exit(0);
            }
            if (event.type == SDL_KEYDOWN)
            {
                keyboard_down(event.key.keysym.sym);
                IFDEBUG("Key pressed");
            }
            else if (event.type == SDL_KEYUP)
            {
                keyboard_up(event.key.keysym.sym);
                IFDEBUG("Key released");
            }
        }

}
static void keyboard_up( SDL_Keycode key)
{
    uint8_t i;
    for (i = 0; i < KEYBOARD_SIZE; i++)
        if (chip8_keyboard.maps[i] == key)
            break;
    if (i == KEYBOARD_SIZE)
    {
        printf("\033[1;31m");
        printf("Error: Key not found\n");
        printf("\033[0m");
        return;
    }
    chip8_keyboard.keys[i] = 0;
}

static void keyboard_down(SDL_Keycode key)
{
    uint8_t i;
    for (i = 0; i < KEYBOARD_SIZE; i++)
        if (chip8_keyboard.maps[i] == key)
            break;
    if (i == KEYBOARD_SIZE)
    {
        printf("\033[1;31m");
        printf("Error: Key not found\n");
        printf("\033[0m");
        return;
    }
    chip8_keyboard.keys[i] = 1;    
}

void keyboard_destroy(Keyboard *keyboard)
{
}

char keyboard_get(Keyboard *keyboard, char key)
{
    return keyboard->keys[key];
}


char keyboard_get_is_change(Keyboard *keyboard)
{
    unsigned char keys[KEYBOARD_SIZE] = {0};
    
    memcpy(keys, keyboard->keys, KEYBOARD_SIZE);

    while(1)
    {
        for (int i = 0; i < KEYBOARD_SIZE; i++)
        {
            if (keys[i] == 0)
                if (keyboard->keys[i])
                    return keyboard->keys[i];
        }
    }

}