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

typedef struct Memory Memory;
struct Memory
{
    void *memory;
    void (*set)(Memory *ram, int index, unsigned char value);
    unsigned char (*get)(Memory *ram, int index);
    void (*init)();
};
typedef struct Display Display;

#endif