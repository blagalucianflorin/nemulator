//
// Created by Blaga Lucian-Florin on 05-Mar-21.
//

#include "include/devices/cpu/6502.h"

#include <iostream>
#include "debugging/6502debugger.h"

cpu::cpu () : device (0x0000, 0x0000) // NOLINT
{
    this -> is_mem   = false;
    this -> populate_operations ();
}

void cpu::write (uint16_t address, uint8_t data, bool from_parent_bus) // NOLINT
{
    (this -> parent_bus) -> write (address, data);
}

uint8_t cpu::read (uint16_t address, bool from_parent_bus) // NOLINT
{
    return ((this -> parent_bus) -> read (address));
}

uint8_t cpu::set_flag (cpu::FLAG flag, uint8_t value)
{
    value = value ? 1 : 0;

    if (this -> get_flag (flag) != value)
        this -> flags_register ^= 1 << flag;

    return (this -> flags_register);
}

uint8_t cpu::get_flag (cpu::FLAG flag)
{
    return (((this -> flags_register) >> flag) & 1);
}

void cpu::reset ()
{
    this -> flags_register         = 0x24;
    this -> accumulator            = 0x00;
    this -> x_register             = 0x00;
    this -> y_register             = 0x00;
    this -> program_counter        = (this -> read (0xFFFD) << 8) | (this -> read (0xFFFC));
    this -> stack_pointer          = 0xFD;

    this -> cycles_left            = 0;
    this -> cycles_elapsed         = 0;
    this -> accumulator_addressing = false;
    this -> jump_relative_address  = 0xFFFF;
    this -> destination_address    = 0xFFFE;

    this -> write (0x4017, 0x00);
    this -> write (0x4015, 0x00);
    for (uint16_t i = 0; i < 16; i++)
        this -> write (0x4000 + i, 0x00);
    for (uint16_t i = 0; i < 4; i++)
        this -> write (0x4010 + i, 0x00);
}

void nop (){}

void cpu::clock ()
{
    if (this -> program_counter >= 0xCFDB && this -> program_counter <= 0xCFDD)
    {
        uint8_t var1 = this -> read (0x0200);
        uint8_t var2 = this -> read (0x0300);
        uint8_t var3 = this -> read (0x0400);
        uint8_t var4 = this -> read (0x0303);
        uint8_t dummy = this -> read (0x0200);
    }

    if (this -> cycles_left == 0)
    {
        std::cout << to_hexa (this -> program_counter, 4) << "  ";
        std::cout << to_hexa (this -> read (this -> program_counter), 2) << " ";

        std::cout << "A:" << to_hexa (this -> accumulator, 2) << " ";
        std::cout << "X:" << to_hexa (this -> x_register, 2) << " ";
        std::cout << "Y:" << to_hexa (this -> y_register, 2) << " ";
        std::cout << "P:" << to_hexa (this -> flags_register, 2) << " ";
        std::cout << "SP:" << to_hexa (this -> stack_pointer, 2) << " ";

        std::cout << "PPU:        CYC:" << this -> cycles_elapsed << " ";

        this ->set_flag (cpu::F_UNUSED, 0);
        uint8_t opcode = this -> read (this -> program_counter);

        (this -> program_counter)++;

        this -> cycles_left += (this -> operations[opcode].cycles_required);
        this -> cycles_left += (this ->* operations[opcode].addressing_mode)();

        this -> accumulator_addressing = this -> operations[opcode].addressing_mode == &cpu::ACC;

        this -> cycles_left += (this ->* operations[opcode].instruction)();

        this ->set_flag (cpu::F_UNUSED, 1);

        if (this -> program_counter >= 0xCFC5 && this -> program_counter <= 0xCFDF)
        {
            std::cout << " MEM: ";
            std::cout << to_hexa (this -> read (0x0200), 2) << " ";
            std::cout << to_hexa (this -> read (0x0300), 2) << " ";
            std::cout << to_hexa (this -> read (0x0303), 2) << " ";
            std::cout << to_hexa (this -> read (0x0400), 2) << " ";
        }
        std::cout << std::endl;
    }
    if (this -> cycles_left != 0)
    {
        (this -> cycles_left)--;
        (this -> cycles_elapsed)++;
    }
}

uint8_t cpu::get_input_data ()
{
    uint8_t input_data;

    if (this -> accumulator_addressing)
        input_data = this -> accumulator;
    else
        input_data = this -> read (this -> destination_address);

    return (input_data);
}

void cpu::push_to_stack(uint8_t value)
{
    this -> write (0x0100 + (this -> stack_pointer), value);
    this -> stack_pointer   -= 1;
}

uint8_t cpu::pull_from_stack ()
{
    this -> stack_pointer   += 1;

    return (this -> read (0x0100 + (stack_pointer)));
}

void cpu::step ()
{
    if (this -> cycles_left != 0)
    {
        while (this -> cycles_left != 0)
            this -> clock ();
    }
    else
    {
        this -> clock ();

        while (this -> cycles_left != 0)
            this -> clock ();
    }
}

void cpu::interrupt (bool force)
{
    if (!force && !(this ->get_flag (cpu::F_INTERRUPT_DISABLE)))
        return;

    this -> step ();

    this -> push_to_stack (this -> program_counter & 0x00FF);
    this -> push_to_stack ((this -> program_counter & 0xFF00) >> 8);
    this -> push_to_stack (this -> flags_register);

    this -> set_flag (cpu::F_INTERRUPT_DISABLE, 1);

    uint16_t address = (force ? 0xFFFA : 0xFFFE);

    this -> program_counter = this -> parent_bus ->read (address) |
                             (this -> parent_bus ->read (address + 1) << 8);
    
    this -> cycles_left += (force ? 8 : 7);
}

void cpu::wait (long cycles)
{
    this -> cycles_left += cycles;
}
