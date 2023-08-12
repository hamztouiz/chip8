#ifndef CHIP8_H
#define CHIP8_H
/* ### Display ### */
#define REGISTER_SIZE 16
#define STACK_SIZE 16
#define KEYBOARD_SIZE 16
#define DEBUG 1
#define IFDEBUG(char) \
    if (DEBUG)        \
        printf("DEBUG: %s:%d: %s\n", __FILE__, __LINE__, char);

typedef struct Memory Memory;
typedef struct CPU CPU;
typedef struct Display Display;
typedef struct Stack Stack;
typedef struct Keyboard Keyboard;

struct CPU
{
    void (*init)(CPU *cpu);
    void (*execute)(CPU *cpu);
    Memory *memory;
    Display *display;
    Keyboard *keyboard;
};
struct Keyboard
{
    unsigned char keys[KEYBOARD_SIZE];
    const char*maps;
    void (*destroy)(Keyboard *keyboard);
    char (*event)(Keyboard *keyboard);
};

struct Display
{
    int width;
    int height;
    char *title;
    void (*init)();
    void (*destroy)();
    void *data;
    unsigned char pixels[64][32];
    void (*print)(Display *display);
    void (*set_pixel)(Display *display, int x, int y);
    void (*clear)(Display *display);
    unsigned char (*drawSprite)(Display *display, int x, int y, unsigned char *sprite, int n);

};
struct Stack
{
    unsigned short stack[STACK_SIZE];
    unsigned char SP;
    void (*push)(Stack *stack, unsigned short value);
    unsigned short (*pop)(Stack *stack);
    void (*init)(Stack *stack);
    void (*destroy)(Stack *stack);
};

struct Memory
{
    void *memory;
    void (*set)(Memory *ram, int index, unsigned char value);
    unsigned char* (*get)(Memory *ram, int index, int length);
    void (*init)(Memory *ram);
    unsigned char (*destroy)(Memory *ram);
    void *(*Delay_timer)();
    void *(*Sound_timer)();
    unsigned short* PC;
    unsigned char registersVX[REGISTER_SIZE]; // V0 - VF*
    unsigned char delay_timer;
    unsigned char sound_timer;

    unsigned short  I;
    Stack stack;

};


#endif