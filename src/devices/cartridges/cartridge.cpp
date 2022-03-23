//
// Created by lblaga on 19.03.2022.
//

#include <iostream>
#include "include/devices/cartridges/cartridge.h"

cartridge::cartridge (const std::string &file_path): device (0x4020, 0xFFFF)
{
    std::string file_format  = file_path.substr (file_path.rfind ('.'));

    this -> program_memory   = nullptr;
    this -> character_memory = nullptr;
    this -> sram             = new uint8_t[0x2000 * sizeof (uint8_t)];
    this -> mapper           = NROM;
    this -> mirroring_type   = HORIZONTAL;

    if (supported_formats.find (file_format) == supported_formats.end ())
        throw cartridge_exception (std::string ("Unsupported file format: ") + file_format);

    read_file_function read_file = supported_formats[file_format];
    (this ->* read_file) (file_path);
}

void cartridge::write (uint16_t address, uint8_t data, bool to_parent_bus) // NOLINT
{
    // CPU writes to SRAM
    if (BETWEEN (0x6000, address, 0x8000))
        this -> sram[address - 0x6000] = data;
    else
        throw cartridge_exception ("Attempted to write to ROM");
}

uint8_t cartridge::read (uint16_t address, bool from_parent_bus) // NOLINT
{
    // CPU reads from PRG
    if (BETWEEN (0x8000, address, 0xFFFF))
        return ((this -> program_memory)[address - 0x8000]);
    // CPU reads from SRAM
    else if (BETWEEN (0x6000, address, 0x8000))
        return ((this -> sram)[address - 0x6000]);
    // PPU reads from CHR
    else if (BETWEEN (0x0000, address, 0x2000))
        return ((this -> character_memory)[address]);
    // TODO check if other locations should be included

    return (0);
}
