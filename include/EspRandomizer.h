#include "Microcontroller.h"

#ifndef ESPRANDOMIZER_H
#define ESPRANDOMIZER_H

class EspRandomizer
{    
public:
    String getHexRandom32();
    unsigned long getRandom32();
};

#endif