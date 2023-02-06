#include "Microcontroller.h"

#ifndef ESPRTCMEMORY_H
#define ESPRTCMEMORY_H

extern "C" {
  #include "user_interface.h"
  extern struct rst_info resetInfo;
}

class EspRtcMemory
{    
public:
    boolean isWakeUpInterrupt();
    uint32_t read(uint32_t offset);
    void write(uint32_t offset, uint32_t data);
};

#endif