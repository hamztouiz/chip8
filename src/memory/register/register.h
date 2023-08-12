#ifndef REGISTER_H
#define REGISTER_H

#include "../../chip8.h"
unsigned char get_register_value(Memory *Memory, unsigned char register_index);
void set_register_value(Memory *Memory, unsigned char register_index, unsigned char value);
void set_register_i(Memory *Memory, unsigned short value);
unsigned short get_register_i(Memory *Memory);
#endif