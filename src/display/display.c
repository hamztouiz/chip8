#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../chip8.h"
#include "display.h"
#define IFDEBUG(char) \
    if (DEBUG)        \
        printf("DEBUG: %s:%d: %s\n", __FILE__, __LINE__, char);

void display_match(Display *display)
{
    display->width = SCREEN_WIDTH;
    display->height = SCREEN_HEIGHT;
    display->title = SCREEN_TITLE;
    display->init = display_init;
    display->destroy = display_quit;
    display->data = (SDL_Window *)NULL;
}

void display_init(Display *display)
{
    SDL_Renderer *renderer;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }
    display->data = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, SDL_WINDOW_SHOWN);
    if (display->data == NULL)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(display->data, -1, SDL_TEXTUREACCESS_TARGET);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = 40;
    r.h = 40;
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);
}

void display_quit(Display *display)
{
    SDL_DestroyWindow(display->data);
    SDL_Quit();
}