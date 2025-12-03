#ifndef _RCSIGNALS_H_
#define _RCSIGNALS_H_

#include <stdint.h>

struct RCSignals
{
    bool regWEn = false;
    bool dmWEn = false;
    bool pcWEn = false;

    uint8_t regWAddr = 0;
    uint32_t regWData = 0;

    uint32_t dmWAddr = 0;
    uint32_t dmWData = 0;
    
    uint32_t pcWData = 0;
};

#endif // _RCSIGNALS_H_