#ifndef KEYBOARDS_H
#define KEYBOARDS_H
#include "../chip8.h"

void keyboard_match(Keyboard *keyboard);
char keyboard_event(Keyboard *keyboard);
void keyboard_destroy(Keyboard *keyboard);

#endif