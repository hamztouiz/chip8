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
    display->print = display_print;
    display->set_pixel = display_set_pixel;
    display->clear = display_clear;
    display->drawSprite = display_drawSprite;

}
static void display_check( int x, int y)
{
    if(x > SCREEN_WIDTH || y > SCREEN_HEIGHT)
    {
        printf("\033[1;31m");
        printf("Error: pixel out of bounds\n");
        printf("\033[0m");
    }
}
void display_init(Display *display)
{
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
}

void display_quit(Display *display)
{
    SDL_DestroyWindow(display->data);
    SDL_Quit();
}

void display_set_pixel(Display *display, int x, int y)
{
    display->pixels[x][y] = 1;
}
void display_clear(Display *display)
{
    for (int i = 0; i < 64; i++)
    {
        for(int j=0; j < 32 ; j++)
        {
            display->pixels[i][j] = 0;
        }
    }
}

void display_print(Display *display)
{
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(display->data, -1, SDL_TEXTUREACCESS_TARGET);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    for (int i = 0; i < 64; i++)
    {
        for(int j=0; j < 32; j++)
        {
            if (display->pixels[i][j] == 1)
            {
                SDL_Rect r;
                r.x = i* 10;
                r.y = j* 10;
                r.w = 10;
                r.h = 10;
                SDL_RenderFillRect(renderer, &r);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

unsigned char display_drawSprite(Display *display, int x, int y, unsigned char *sprite, int n)
{
    unsigned char result = 0;
    for (int i = 0; i < n; i++)
    {
        unsigned char byte = sprite[i];

        for (int j = 0; j < 8; j++)
        {
            if ( (byte >> (7 - j)) & 1)
            {
                display_set_pixel(display, x + j, y + i);
            }
            if (display->pixels[x + j][y + i] == 1)
            {
                result = 1;
            }

        }

    }
    return result;
}
