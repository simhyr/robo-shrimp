#include "EspRandomizer.h"

unsigned long EspRandomizer::getRandom32() 
{
    return ESP.random();
}


String EspRandomizer::getHexRandom32() 
{
    auto id = getRandom32();

    char str[11];
    // pad string to 10 digit hexadecimal with leading zeros and starting with 0x
    sprintf(str, "%#010lx", id);

    return String(str);
}