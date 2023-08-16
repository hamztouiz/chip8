#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void print_error_opcode(unsigned short opcode);

void cpu_match(CPU * cpu)
{
    cpu-> fetch = cpu_fetch;
    cpu->decode = cpu_decode;
    cpu->execute = cpu_execute;

}
 unsigned char* cpu_fetch(CPU* cpu, Memory* memory)
{
    unsigned char *instruction = NULL;
    instruction = memory->get(*memory,memory->PC, 2);
    memory->PC= memory->PC + 2;
    return instruction;

}
unsigned char* cpu_decode(CPU* cpu , unsigned char *instruction)
{
    unsigned char *nibble = malloc(sizeof(unsigned char) * 4);
    for( unsigned char i =0; i< 4; i++)
    {
        unsigned char tmp = 0 ; 
        tmp = instruction[i/2] ; 
        if ( i % 2 ==  0)
                tmp = tmp >> 4;

        nibble[i] = tmp & 0b00001111 ;

    }
    return nibble;
}
void cpu_execute(CPU* cpu, Memory* memory, Display* display, Keyboard* keyboard, unsigned char * niblle, unsigned char *instruction)
{
unsigned short opcode = 0;
opcode = instruction[0] << 8 | instruction[1];
printf("opcode : %x\n", opcode);
 switch (niblle[0])
{
    case 0 :
        switch (opcode)
        {
            case CLS:
                display->clear(display);
                break;
            case RET:
                memory->PC = memory->stack.pop(&(memory->stack));
                break;
            default: // SYS 
            break;
        }
        break;
    case 1 : // JP
        memory->PC= opcode & 0x0FFF;
        break;
    case 2 : // CALL
        memory->stack.push(&(memory->stack), memory->PC);
        memory->PC = opcode & 0x0FFF;
        break;
    case 3 : // SE Vx, byte
        if( memory->registersVX[niblle[1]] == opcode & 0x00FF)
            memory->PC = memory->PC + 2;
        break;
    case 4 : // SNE Vx, byte
        if( memory->registersVX[niblle[1]] != opcode & 0x00FF)
            memory->PC = memory->PC + 2;
        break;
    case 5 : // SE Vx, Vy
        if( memory->registersVX[niblle[1]] == memory->registersVX[niblle[2]])
            memory->PC = memory->PC + 2;
        break;
    case 6 : // LD Vx, byte
        memory->registersVX[niblle[1]] = opcode & 0x00FF;
        break;
    // to 0xF
    case 7 : // ADD Vx, byte
        memory->registersVX[niblle[1]] = memory->registersVX[niblle[1]] + (opcode & 0x00FF);
        break;
    case 8 : 
        switch (niblle[3])
        {
            case 0: // LD Vx, Vy
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[2]];
            break;
            case 1:
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[1]] | memory->registersVX[niblle[2]];
                break;
            case 2:
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[1]] & memory->registersVX[niblle[2]];
                break;
            case 3:
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[1]] ^ memory->registersVX[niblle[2]];
                break;
            case 4: 
                int i = memory->registersVX[niblle[1]] + memory->registersVX[niblle[2]];
                if ( i > 255)
                    memory->registersVX[0xF] = 1;
                else
                    memory->registersVX[0xF] = 0;
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[1]] + memory->registersVX[niblle[2]];
                break;
            case 5:
                if ( memory->registersVX[niblle[1]] > memory->registersVX[niblle[2]])
                    memory->registersVX[0xF] = 1;
                else
                    memory->registersVX[0xF] = 0;
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[1]] - memory->registersVX[niblle[2]];
                break;
            case 6:
                memory->registersVX[0xF] = memory->registersVX[niblle[1]] & 0x1;
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[1]] >> 1;
                break;
            case 7:
                if(memory->registersVX[niblle[2]] > memory->registersVX[niblle[1]])
                    memory->registersVX[0xF] = 1;
                else
                    memory->registersVX[0xF] = 0;
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[2]] - memory->registersVX[niblle[1]];
                break;
            case 0xE:
                memory->registersVX[0xF] = memory->registersVX[niblle[1]] & 0x80;
                memory->registersVX[niblle[1]] = memory->registersVX[niblle[1]] << 1;
                break;
            default:
                print_error_opcode(opcode);
                break;
            }
    break;
    case 9 : // SNE Vx, Vy
        if( memory->registersVX[niblle[1]] != memory->registersVX[niblle[2]])
            memory->PC = memory->PC + 2;
        break;
    break;
    case 0xA : // LD I, addr
        memory->I = opcode & 0x0FFF;
        break;
    case 0xB : // JP V0, addr
        memory->PC = opcode & 0x0FFF + memory->registersVX[0];
        break;
    case 0xC : // RND Vx, byte
        memory->registersVX[niblle[1]] = (rand()%256) & (opcode & 0x00FF);
        break;
    case 0xD : // DRW Vx, Vy, nibble
        unsigned char *sprite = memory->get(*memory, memory->I, niblle[3]);
        memory->registersVX[0xF] = display->drawSprite(display, memory->registersVX[niblle[1]], memory->registersVX[niblle[2]],sprite, niblle[3]);
        free(sprite);
        break;
    case 0xE :
        switch (niblle[3])
        {
            case 0xE :
                if (keyboard->get(keyboard, memory->registersVX[niblle[1]]))
                    memory->PC = memory->PC + 2;
                break;
            break;
            case 0x1 :
                if (!keyboard->get(keyboard, memory->registersVX[niblle[1]]))
                    memory->PC = memory->PC + 2;
                break;
            break;
            default:
                    print_error_opcode(opcode);
            break;
        }
        break;
    case 0xF :
        switch (opcode & 0x00FF)
        {
            case 0x07 :
            memory->registersVX[niblle[1]] = memory->delay_timer;
            break;
            case 0x0A :
            memory->registersVX[niblle[1]] = keyboard->keyboard_get_is_change(keyboard);
            break;
            case 0x15 :
            memory->delay_timer = memory->registersVX[niblle[1]];
            break;
            case 0x18 :
            memory->sound_timer = memory->registersVX[niblle[1]];
            break;
            case 0x1E :
            memory->I = memory->I + memory->registersVX[niblle[1]];
            break;
            case 0x29 :
            memory->I = memory->registersVX[niblle[1]] * 5;
            break;
            case 0x33 :
            memory->set(memory, memory->I, memory->registersVX[niblle[1]] / 100);
            memory->set(memory, memory->I + 1, (memory->registersVX[niblle[1]] / 10) % 10);
            memory->set(memory, memory->I + 2, (memory->registersVX[niblle[1]] % 100) % 10);
            break;
            case 0x55 :
                for (int i = 0; i <= niblle[1]; i++)
                    memory->set(memory, memory->I + i, memory->registersVX[i]);
                break;
            case 0x65 :
                unsigned char *tmp = memory->get(*memory, memory->I, niblle[1]);
                for (int i = 0; i <= niblle[1]; i++)
                    memory->registersVX[i] = tmp[i];
                free(tmp);
                break;
            default:
                    print_error_opcode(opcode);
            break;
        }
        break;

    default:
        break;
    }
}

void static print_error_opcode(unsigned short opcode)
{
    printf("\033[1;31m");
    printf("Error opcode : %x\n", opcode);
    printf("\033[0m");
    //exit(1);

}