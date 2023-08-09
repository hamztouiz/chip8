#include "ram.h"
#include <stdlib.h>
#include <string.h>

void Ram_match(Ram *Ram)
{
    Ram->memory = (unsigned char *)malloc(sizeof(unsigned char) * 4096);
    Ram->set = Ram_set;
    Ram->get = Ram_get;
    Ram->init = Ram_init;
}
void Ram_init(Ram *Ram)
{
    memset(Ram->memory, 0, sizeof(Ram->memory));
}
void Ram_set(Ram *Ram, int index, unsigned char value)
{
    ((unsigned char *)Ram->memory)[index] = value;
}

unsigned char Ram_get(Ram *Ram, int index)
{

    return ((unsigned char *)Ram->memory)[index];
}