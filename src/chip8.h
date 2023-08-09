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

typedef struct Ram Ram;
struct Ram
{
    void *memory;
    void (*set)(Ram *ram, int index, unsigned char value);
    unsigned char (*get)(Ram *ram, int index);
    void (*init)();
};
typedef struct Display Display;

#endif