#ifndef DISPLAY_H
#define DISPLAY_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define SCREEN_TITLE "Chip-8 Emulator"
void display_match(Display *display);
void display_init(Display *display);
void display_quit(Display *display);
void display_print(Display *display);
void display_set_pixel(Display *display, int x, int y);
void display_clear(Display *display);
unsigned char display_drawSprite(Display *display, int x, int y, unsigned char *sprite, int n);
#endif