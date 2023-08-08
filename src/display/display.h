#ifndef DISPLAY_H
#define DISPLAY_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define SCREEN_TITLE "Chip-8 Emulator"
void display_match(Display *display);
void display_init(Display *display);
void display_quit(Display *display);
#endif