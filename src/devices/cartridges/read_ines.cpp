//
// Created by lblaga on 20.03.2022.
//

#include "include/devices/cartridges/cartridge.h"

void cartridge::read_ines (const std::string& file_path)
{
    char          format_check[5],  padding[8];
    uint8_t       program_size,     character_size, program_ram_size;
    uint8_t       control_byte_one, control_byte_two;
    std::ifstream file (file_path, std::ios_base::binary);

    // Read header and check integrity
    format_check[4] = padding[7] = '\0';
    file.read (format_check, 4);
    file.get ((char&) program_size);
    file.get ((char&) character_size);
    file.get ((char&) control_byte_one);
    file.get ((char&) control_byte_two);
    file.get ((char&) program_ram_size);
    file.read (padding, 7);

    if (std::string (format_check) != "NES\x1A" || std::string (padding) != "\0\0\0\0\0\0\0\0") // NOLINT
        throw cartridge_exception ("iNES: Corrupted file header");

    this -> program_memory   = new uint8_t[std::max (program_size, (uint8_t) 2) * 16384 * sizeof (uint8_t)];
    this -> character_memory = new uint8_t[character_size * 8192 * sizeof (uint8_t)];

    if ((control_byte_two & 0b00001111) != 0)
        throw cartridge_exception ("iNES: Only iNES 1.0 is supported");

    if ((control_byte_one & 0b00001000) != 0)
        this -> mirroring_type = FOUR_SCREEN;
    else if ((control_byte_one & 0b00000001) != 0)
        this -> mirroring_type = VERTICAL;
    else
        this -> mirroring_type = HORIZONTAL;

    // TODO find a more easily extendable mechanism for checking mappers
    if ((control_byte_one & 0xF0 | control_byte_two & 0xF) != 0)
        throw cartridge_exception ("iNES: Unsupported mapper");

    // Read contents
    file.read ((char*) this -> program_memory, (long) (program_size * 16384 * sizeof (uint8_t)));
    // Check if trainer exists
    if ((control_byte_one & 0b00000100) != 0)
        file.read ((char*) this -> sram + 4096, (long) (512 * sizeof(uint8_t)));
    file.read ((char*) this -> character_memory, (long) (character_size * 8192 * sizeof (uint8_t)));

    // Mirror contents of first 16K of PRG is only one memory block is present
    if (program_size == 1)
        std::memcpy (this -> program_memory + 16384, this -> program_memory, 16384);

    this -> mapper = NROM;
}