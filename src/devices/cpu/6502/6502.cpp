//
// Created by Blaga Lucian-Florin on 05-Mar-21.
//

#include "include/devices/cpu/6502.h"

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
    this -> flags_register         = 0b00000000;
    this -> accumulator            = 0x00;
    this -> x_register             = 0x00;
    this -> y_register             = 0x00;
    this -> program_counter        = 0x0000;
    this -> stack_pointer          = 0xFF;

    this -> cycles_left            = 0;
    this -> cycles_elapsed         = 0;
    this -> accumulator_addressing = false;
    this -> jump_relative_address  = 0xFFFF;
    this -> destination_address    = 0xFFFE;
}

void cpu::clock ()
{
    if (this -> cycles_left == 0)
    {
        uint8_t opcode = this -> read (this -> program_counter);

        (this -> program_counter)++;

        this -> cycles_left += (this -> operations[opcode].cycles_required);
        this -> cycles_left += (this ->* operations[opcode].addressing_mode)();

        this -> accumulator_addressing = this -> operations[opcode].addressing_mode == &cpu::ACC;

        this -> cycles_left += (this ->* operations[opcode].instruction)();
    }
    (this -> cycles_left)--;
    (this -> cycles_elapsed)++;
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

void cpu::force_interrupt () {}

void cpu::interrupt () {}
