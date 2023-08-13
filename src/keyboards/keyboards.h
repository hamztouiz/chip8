#ifndef KEYBOARDS_H
#define KEYBOARDS_H
#include "../chip8.h"

void keyboard_match(Keyboard *keyboard);
void *keyboard_event();
void keyboard_destroy(Keyboard *keyboard);
char keyboard_get(Keyboard *keyboard, char key);
char keyboard_get_is_change(Keyboard *keyboard);

#endif