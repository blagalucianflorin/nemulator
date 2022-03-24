//
// Created by lblaga on 20.03.2022.
//

#include <iostream>
#include "include/devices/ppu/ppu.h"

ppu::ppu (SDL_Renderer *renderer, class cpu *cpu, int x_offset, int y_offset) : device (0x2000, 0x3FFF)
{
    this -> renderer = renderer;
    this -> x_offset = x_offset;
    this -> y_offset = y_offset;
    this -> cpu      = cpu;
}

void ppu::write (uint16_t address, uint8_t data, bool to_parent_bus) // NOLINT
{
    if (to_parent_bus)
    {
        address = (address - 0x2000) % 8;

        switch (address) {
            case 0x0000:
                break;
            case 0x0001:
                break;
            case 0x0002:
                throw ppu_exception("Tried to write to status register");
            case 0x0003:
                break;
            case 0x0004:
                break;
            case 0x0005:
                break;
            case 0x0006:
                set_destination_address (data);
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
        if (BETWEEN (0x2000, address, 0x3FFF)) {
            address = (address - 0x2000) % 8;

            switch (address) {
                case 0x0000:
                    throw ppu_exception("Tried to read from control register");
                case 0x0001:
                    throw ppu_exception("Tried to read from mask register");
                case 0x0002:
                    return (0);
                case 0x0003:
                    return (this->oam_address_register);
                case 0x0004:
                    return (this->oam_data_register);
                case 0x0005:
                    throw ppu_exception("Tried to read from scroll register");
                case 0x0006:
                    return (this -> address_register);
                case 0x0007:
                    return get_data_register ();
                default:
                    break;
            }
        }
        else
        {
            return ((this -> parent_bus) -> read (address));
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

uint8_t ppu::get_status_flag (ppu::STATUS_FLAG flag)
{
    return (((this -> status_register) >> flag) & 1);
}

void ppu::set_destination_address (uint8_t data)
{
    if (this -> destination_address_low_byte)
        this -> destination_address  = data;
    else
        this -> destination_address = (this -> destination_address << 8) | data;

    this -> destination_address_low_byte = !(this -> destination_address_low_byte);
}

uint8_t ppu::get_data_register ()
{
    uint8_t previous_data = this -> data_register;

    this -> data_register = child_bus -> read (this -> destination_address);
    if (!BETWEEN (0x0000, this -> destination_address, 0x2FFF))
        previous_data = child_bus -> read (this -> destination_address);

    this -> address_register += (get_control_flag (F_ADDRESS_INCREMENT) == 1 ? 32 : 1);

    return (previous_data);
}

void ppu::clock ()
{
    this -> current_cycle = (this -> current_cycle + 1) % 89342;
    if (this -> current_cycle == 89340)
        (this -> frames_rendered)++;

    // TODO draw a pixel
    SDL_SetRenderDrawColor (this -> renderer, 0, 128, 0, 0);
    if (this -> scancolumn <= 256 && this -> scanline <= 240)
        SDL_RenderDrawPoint (this -> renderer, (this -> scancolumn) + (this -> x_offset),
                             (this -> scanline) + (this -> y_offset));

    (this -> scancolumn)++;
    if (this -> scancolumn == 341)
    {
        this -> scancolumn = 0;
        (this -> scanline)++;
        if (this -> scanline == 262)
        {
            this -> scanline = 0;
        }
        else if (this -> scanline == 240 && this -> get_control_flag (ppu::F_NMI_ON_VBLANK))
        {
            cpu -> interrupt (true);
        }
    }
}
