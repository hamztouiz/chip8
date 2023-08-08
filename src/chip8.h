#ifndef CHIP8_H
#define CHIP8_H
/* ### Display ### */
struct Display
{
    int width;
    int height;
    char *title;
    void (*init)();
    void (*destroy)();
    void *data;
};
struct ram
{
    unsigned char memory[4096];
};
typedef struct Display Display;
typedef struct ram ram;

#endif