//
// Created by lblaga on 20.03.2022.
//

#ifndef NEMULATOR_PPU_H
#define NEMULATOR_PPU_H

#include "include/devices/device.h"
#include "include/devices/ppu/exceptions/ppu_exception.h"
#include "include/bus/bus.h"
#include "include/forwards/classes.h"
#include "include/misc/macros.h"
#include "include/devices/cpu/6502.h"

#include <SDL2/SDL.h>
#include <random>

class ppu : public device
{
#ifdef G_TESTING
public:
#else
    private:
#endif
    uint8_t control_register     = 0x0000;
    uint8_t mask_register        = 0x0000;
    uint8_t status_register      = 0x0000;
    uint8_t oam_address_register = 0x0000;
    uint8_t oam_data_register    = 0x0000;
    uint8_t scroll_register      = 0x0000;
    uint8_t address_register     = 0x0000;
    uint8_t data_register        = 0x0000;

    uint8_t oam_dma_register     = 0x0000;

    uint16_t destination_address          = 0x0000;
    bool     destination_address_low_byte = true;

    enum CONTROL_FLAG
    {
        F_NAME_TABLE_ADDRESS_ONE   = 0,
        F_NAME_TABLE_ADDRESS_TWO   = 1,
        F_ADDRESS_INCREMENT        = 2,
        F_SPRITE_PATTERN_TABLE     = 3,
        F_BACKGROUND_PATTERN_TABLE = 4,
        F_SPRITE_SIZE              = 5,
        F_PPU_SELECT               = 6, // Unused
        F_NMI_ON_VBLANK            = 7
    };

    enum MASK_FLAG
    {
        F_GREYSCALE              = 0,
        F_SPRITE_CLIPPING        = 1,
        F_BACKGROUND_CLIPPING    = 2,
        F_SHOW_SPRITES           = 3,
        F_SHOW_BACKGROUND        = 4,
        F_BACKGROUND_COLOR_ONE   = 5,
        F_BACKGROUND_COLOR_TWO   = 6,
        F_BACKGROUND_COLOR_THREE = 7,
    };

    enum STATUS_FLAG
    {
        F_LAST_WRITE_BIT_ONE   = 0,
        F_LAST_WRITE_BIT_TWO   = 1,
        F_LAST_WRITE_BIT_THREE = 2,
        F_LAST_WRITE_BIT_FOUR  = 3,
        F_LAST_WRITE_BIT_FIVE  = 4,
        F_SPRITE_OVERFLOW      = 5,
        F_SPRITE_ZERO_HIT      = 6,
        F_VBLANK_STARTED       = 7
    };

    void    set_destination_address (uint8_t data);

    uint8_t get_data_register ();

    void    clock ();

    int     current_cycle = 0;
    long    frames_rendered = 0;

    int     scanline = 0;
    int     scancolumn = 0;

    SDL_Renderer *renderer = nullptr;
    int          x_offset  = 0;
    int          y_offset  = 0;

    class cpu *cpu = nullptr;

public:
    ppu (SDL_Renderer *renderer, class cpu *cpu, int x_offset = 0, int y_offset = 0);

    void     write (uint16_t address, uint8_t data, bool to_parent_bus = true) override; // NOLINT

    uint8_t  read (uint16_t address, bool from_parent_bus = true) override; // NOLINT

    uint8_t  set_control_flag (CONTROL_FLAG flag, uint8_t value);

    uint8_t  get_control_flag (CONTROL_FLAG flag);

    uint8_t  set_mask_flag (MASK_FLAG flag, uint8_t value);

    uint8_t  get_mask_flag (MASK_FLAG flag);

    uint8_t  get_status_flag (STATUS_FLAG flag);
};

#endif //NEMULATOR_PPU_H
