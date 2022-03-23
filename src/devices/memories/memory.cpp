//
// Created by Blaga Lucian-Florin on 05-Mar-21.
//

#include "include/devices/memories/memory.h"

memory::memory (uint16_t lower_bound, uint16_t upper_bound)
                : device (lower_bound, upper_bound)
{
    this -> internal_memory = new uint8_t[upper_bound - lower_bound];
}