//
// Created by lblaga on 20.03.2022.
//

#include <iostream>
#include "include/devices/ppu/ppu.h"

ppu::ppu (SDL_Renderer *renderer) : device (0x2000, 0x3FFF)
{
    this -> renderer = renderer;
}

void    ppu::reset ()
{
    this -> current_cycle = 0;
}

void    ppu::write (uint16_t address, uint8_t data, bool to_parent_bus) // NOLINT
{
    if (to_parent_bus)
    {
        address = (address - 0x2000) % 8;

        switch (address) {
            case 0x0000:
                if (current_cycle >= 30000)
                    this -> control_register = data;
            case 0x0001:
                this -> mask_register = data;
            case 0x0002:
                throw ppu_exception("Tried to write to status register");
            case 0x0003:
                this -> oam_address_register = data;
            case 0x0004:
                this -> oam_data_register = data;
                (this -> oam -> memory)[oam_address_register] = data;
                (this -> oam_address_register)++;
            case 0x0005: case 0x0006:
                build_destination_address (data);
            case 0x0007:
                this -> data_register    = data;
                this -> address_register += (get_control_flag (F_ADDRESS_INCREMENT) == 1 ? 32 : 1);
            default:
                break;
        }
    }
    else
        (this -> child_bus) -> write (address, data);
}

uint8_t ppu::read (uint16_t address, bool from_parent_bus) // NOLINT
{
    if (from_parent_bus)
    {
        if (!BETWEEN (0x2000, address, 0x3FFF))
            return ((this -> parent_bus) -> read (address));

        address = (address - 0x2000) % 8;

        switch (address)
        {
            case 0x0000:
                throw ppu_exception ("Tried to read from control register");
            case 0x0001:
                throw ppu_exception ("Tried to read from mask register");
            case 0x0002:
                return (this -> get_status_register ());
            case 0x0003:
                return (this -> oam_address_register);
            case 0x0004:
                this -> oam_data_register = (this -> oam -> memory)[this -> oam_address_register];

                return (this -> oam_data_register);
            case 0x0005:
                throw ppu_exception ("Tried to read from scroll register");
            case 0x0006:
                throw ppu_exception ("Tried to read from address register");
            case 0x0007:
                return get_data_register ();
            default:
                break;
        }
    }
    else
        return ((this -> child_bus) -> read (address));

    return (0);
}

uint8_t ppu::set_control_flag (ppu::CONTROL_FLAG flag, uint8_t value)
{
    value = value ? 1 : 0;

    if (this -> get_control_flag (flag) != value)
        this -> control_register ^= 1 << flag;

    return (this -> control_register);
}

uint8_t ppu::get_control_flag (ppu::CONTROL_FLAG flag)
{
    return (((this -> control_register) >> flag) & 1);
}

uint8_t ppu::set_mask_flag (ppu::MASK_FLAG flag, uint8_t value)
{
    value = value ? 1 : 0;

    if (this -> get_mask_flag (flag) != value)
        this -> mask_register ^= 1 << flag;

    return (this -> mask_register);
}

uint8_t ppu::get_mask_flag (ppu::MASK_FLAG flag)
{
    return (((this -> mask_register) >> flag) & 1);
}

uint8_t ppu::set_status_flag (ppu::STATUS_FLAG flag, uint8_t value)
{
    value = value ? 1 : 0;

    if (this -> get_status_flag (flag) != value)
        this -> status_register ^= 1 << flag;

    return (this -> status_register);
}

uint8_t ppu::get_status_flag (ppu::STATUS_FLAG flag)
{
    return (((this -> status_register) >> flag) & 1);
}

void    ppu::build_destination_address (uint8_t data)
{
    if (this -> address_latch)
        this -> destination_address = (this -> destination_address << 8) | data;
    else
        this -> destination_address  = data;

    this -> address_latch = !(this -> address_latch);
}

void    ppu::build_scroll_register (uint8_t data)
{
    if (this -> address_latch)
        this -> destination_address = (this -> destination_address << 8) | data;
    else
        this -> destination_address  = data;

    this -> address_latch = !(this -> address_latch);
}

uint8_t ppu::get_data_register ()
{
    this -> previous_data = this -> data_register;

    this -> data_register = child_bus -> read (this -> destination_address);
    if (!BETWEEN (0x0000, this -> destination_address, 0x2FFF))
        this -> previous_data = child_bus -> read (this -> destination_address);

    this -> address_register += (get_control_flag (F_ADDRESS_INCREMENT) == 1 ? 32 : 1);

    return (this -> previous_data);
}

uint8_t ppu::get_status_register ()
{
    uint8_t result = ((this -> status_register & 0b11100000) | (this -> previous_data & 0b00011111));

    this -> set_status_flag (STATUS_FLAG::F_VBLANK_STARTED, 0);
    this -> address_latch = true;

    return (result);
}

void    ppu::clock ()
{
    // TODO draw a pixel
//    SDL_SetRenderDrawColor (this -> renderer, 0, 128, 0, 0);
//    if (this -> dot <= 256 && this -> scanline <= 240)
//        SDL_RenderDrawPoint (this -> renderer, (this -> dot) + (this -> x_offset),
//                             (this -> scanline) + (this -> y_offset));

    (this -> dot)++;
    if (this -> dot == 341)
    {
        this -> dot = 0;
        (this -> scanline)++;
        if (this -> scanline == 262)
        {
            this -> set_status_flag (STATUS_FLAG::F_VBLANK_STARTED, 0);
            this -> scanline = 0;
        }
        else if (this -> scanline == 240 && this -> get_control_flag (ppu::F_NMI_ON_VBLANK))
        {
            this -> set_status_flag (STATUS_FLAG::F_VBLANK_STARTED, 1);
            cpu -> interrupt (true);
        }
    }
}
