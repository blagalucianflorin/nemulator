//
// Created by lblaga on 26.03.2022.
//

#include "include/devices/ppu/oam.h"

oam::oam () : device (0x4014, 0x4014) {} // NOLINT

void oam::write (uint16_t address, uint8_t data, bool to_parent_bus) // NOLINT
{
    this -> dma_register = data;

    this -> cpu -> wait (this -> cpu -> get_cycles_elapsed () % 2 == 0 ? 513 : 514);

    for (uint16_t i = this -> read (0x2003); i < 256; i++)
    {
        (this -> memory)[i] = this -> cpu -> read ((((uint16_t) data) << 8 & 0xFF00) + i);
        this -> write (0x2004, (this -> memory)[i]);
    }
}

uint8_t oam::read (uint16_t address, bool from_parent_bus) // NOLINT
{
    throw ppu_exception ("OAM: Tried to read from OAM DMA register");
}
