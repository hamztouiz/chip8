#include "timer.h"
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

extern Memory chip8_Memory;

void *Timer_delay()
{
    while (1)
    {
        if(chip8_Memory.delay_timer > 0)
        {
            usleep((1000*1000)/60);
            chip8_Memory.delay_timer--;
        } 

    }
}

void *Timer_sound()
{
    initscr();
    beep();
            refresh();
    while (1)
    {
        if(chip8_Memory.sound_timer > 0)
        {
            usleep((1000*1000)/60);
           
            chip8_Memory.sound_timer--;
            IFDEBUG("Sound timer: sound_timer");

            

        } 

    }
}