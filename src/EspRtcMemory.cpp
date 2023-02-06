#include "EspRtcMemory.h"

boolean EspRtcMemory::isWakeUpInterrupt() 
{
    auto resetInfo = ESP.getResetInfoPtr();

    if(resetInfo->reason == REASON_DEEP_SLEEP_AWAKE)
        return true;

    return false;
}

uint32_t EspRtcMemory::read(uint32_t offset)
{
    uint32_t data = 0;
    if(isWakeUpInterrupt()) 
        ESP.rtcUserMemoryRead(offset, &data, sizeof(data));

    return data;
}

void EspRtcMemory::write(uint32_t offset, uint32_t data) 
{
    ESP.rtcUserMemoryWrite(0, &data, sizeof(data));
}