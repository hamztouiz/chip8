#include "timer.h"
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

extern Memory chip8_Memory;

void *Timer_delay()
{
    while (1)
    {
        if(chip8_Memory.delay_timer > 0)
        {
            usleep((1000)/60);
            chip8_Memory.delay_timer--;
        } 

    }
}

void *Timer_sound()
{

if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    // Gestion de l'erreur d'ouverture audio
    printf("Error: %s\n", Mix_GetError());

}
    Mix_Chunk *audioChunk = Mix_LoadWAV("/home/hamzux/projet/chip8/media/beep.wav");
    
    if (audioChunk == NULL) {
        // in  red
        printf("Error: %s\n", Mix_GetError());

    }
    while (1)
    {
        if(chip8_Memory.sound_timer > 0)
        {
            int channel = Mix_PlayChannel(-1, audioChunk, 0);
            if (channel == -1) {
                // in  red
                printf("Error: %s\n", Mix_GetError());
            }
            usleep((1000)/60);
            chip8_Memory.sound_timer--;
//            IFDEBUG("Sound timer: sound_timer");

        } 

    }
}