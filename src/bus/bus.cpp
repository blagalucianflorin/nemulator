//
// Created by Blaga Lucian-Florin on 05-Mar-21.
//

#include "include/bus/bus.h"
#include "include/misc/macros.h"


void bus::add_device (device *new_device)
{
    (this -> devices).push_back (new_device);
    new_device -> set_parent_bus (*this);
}

void bus::write (uint16_t address, uint8_t data)
{
    if (!BETWEEN (this -> lower_bound, address, this -> upper_bound))
        throw std::invalid_argument ("Bus: Tried to write outside of addressable range");

    for (auto device : this -> devices)
        if (BETWEEN (device -> get_lower_bound (), address,device -> get_upper_bound ()) && device -> is_memory ())
        {
            device -> write (address, data);
            break;
        }
}

uint8_t bus::read (uint16_t address)
{
    if (!BETWEEN (this -> lower_bound, address, this -> upper_bound))
        throw std::invalid_argument ("Bus: Tried to read from outside of addressable range");

    for (auto device : this -> devices)
        if (BETWEEN (device -> get_lower_bound (), address, device -> get_upper_bound ()) && device -> is_memory ())
            return (device -> read (address));

    return (-1);
}