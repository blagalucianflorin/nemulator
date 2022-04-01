//
// Created by Blaga Lucian-Florin on 07-Mar-21.
//

#include "include/devices/cpu/6502.h"
#include <iostream>
#include "debugging/6502debugger.h"


uint8_t cpu::IMP () // NOLINT
{
    std::cout << "     ";

    return (0);
}

uint8_t cpu::ACC ()
{
//    (this -> program_counter)++;

    return (0);
}

uint8_t cpu::IMM ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << "   ";

    this -> destination_address = this -> program_counter;
    (this -> program_counter)++;

    return (0);
}

uint8_t cpu::ZPG ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << "   ";

    this -> destination_address = this -> read (this -> program_counter);
    (this -> program_counter)++;

    return (0);
}

uint8_t cpu::ZPX ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << "   ";

    this -> destination_address = this -> read (this -> program_counter);
    this -> destination_address += this -> x_register;
    this -> destination_address &= 0x00FF;
    (this -> program_counter)++;

    return (0);
}

uint8_t cpu::ZPY ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << "   ";

    this -> destination_address = this -> read (this -> program_counter);
    this -> destination_address += this -> y_register;
    this -> destination_address &= 0x00FF;
    (this -> program_counter)++;

    return (0);
}

uint8_t cpu::REL ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << "   ";

    this -> jump_relative_address = this -> read (this -> program_counter);
    (this -> program_counter)++;

    if (this -> jump_relative_address & 0x80)
    {
        this->jump_relative_address |= 0xFF00;
        return (1);
    }

    return (0);
}

uint8_t cpu::ABS ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << " ";
    std::cout << to_hexa (this -> read (this -> program_counter + 1), 2);

    this -> destination_address = 0x0000 | this -> read (this -> program_counter++);
    this -> destination_address |= this -> read (this -> program_counter++) << 8;

    return (0);
}

uint8_t cpu::ABX ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << " ";
    std::cout << to_hexa (this -> read (this -> program_counter + 1), 2);

    uint16_t aux_1;
    uint16_t aux_2;

    aux_1                       = this -> read (this -> program_counter++);
    aux_2                       = this -> read (this -> program_counter++);
    this -> destination_address = (aux_2 << 8) | aux_1;

    this -> destination_address += this -> x_register;

    if (((this -> destination_address) & 0xFF00) != ((aux_2 << 8) & 0xFF00))
        return (1);

    return (0);
}

uint8_t cpu::ABY ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << " ";
    std::cout << to_hexa (this -> read (this -> program_counter + 1), 2);

    uint16_t aux_1;
    uint16_t aux_2;

    aux_1                       = this -> read (this -> program_counter++);
    aux_2                       = this -> read (this -> program_counter++);
    this -> destination_address = (aux_2 << 8) | aux_1;

    this -> destination_address += this -> y_register;

    if (((this -> destination_address) & 0xFF00) != ((aux_2 << 8) & 0xFF00))
        return (1);

    return (0);
}

uint8_t cpu::IND ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << " ";
    std::cout << to_hexa (this -> read (this -> program_counter + 1), 2);

    uint8_t  pointer_low_byte;
    uint8_t  pointer_high_byte;
    uint8_t  dest_low_byte;
    uint8_t  dest_high_byte;
    uint16_t destination;
    uint16_t pointer;

    pointer_low_byte = this -> read (this -> program_counter);
    (this -> program_counter)++;
    pointer_high_byte  = this -> read (this -> program_counter);

    pointer       = (((uint16_t) pointer_high_byte) << 8) + pointer_low_byte;
    dest_low_byte = this -> read (pointer);
    if (pointer_low_byte == 0xFF)
    {
        pointer        = (((uint16_t) pointer_high_byte) << 8) & 0xFF00;
        dest_high_byte = this -> read (pointer);
    }
    else
        dest_high_byte = this -> read (pointer + 1);

    destination                 = (((uint16_t) dest_high_byte) << 8) + dest_low_byte;
    this -> destination_address = destination;

    return (0);
}

uint8_t cpu::IDX ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << "   ";

    uint8_t aux_adr;
    uint8_t aux_1;
    uint8_t aux_2;

    aux_adr = this -> read (this -> program_counter);
    (this -> program_counter)++;

    aux_1 = this -> read ((uint16_t)(aux_adr + ((uint16_t)this -> x_register)) & 0x00FF);
    aux_2  = this -> read ((uint16_t)(aux_adr + ((uint16_t)this -> x_register) + 1) & 0x00FF);

    this -> destination_address = (uint16_t)(aux_2 << 8) | aux_1;

    return (0);
}

uint8_t cpu::IDY ()
{
    std::cout << to_hexa (this -> read (this -> program_counter), 2) << "   ";

    uint8_t aux_adr;
    uint8_t aux_1;
    uint8_t aux_2;

    aux_adr = this -> read (this -> program_counter);
    (this -> program_counter)++;

    aux_1 = this -> read (aux_adr & 0x00FF);
    aux_2 = this -> read ((aux_adr + 1) & 0x00FF);

    this -> destination_address = (aux_2 << 8) + aux_1;
    this -> destination_address += this -> y_register;

    if (((this -> destination_address) & 0xFF00) >> 8 != aux_2)
        return (1);

    return (0);
}