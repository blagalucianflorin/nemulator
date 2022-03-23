//
// Created by Blaga Lucian-Florin on 07-Mar-21.
//

#include "include/devices/cpu/6502.h"


void cpu::populate_operations ()
{
    // ADC
    (this -> operations)[0x69] = {&cpu::ADC, &cpu::IMM, 2};
    (this -> operations)[0x65] = {&cpu::ADC, &cpu::ZPG, 3};
    (this -> operations)[0x75] = {&cpu::ADC, &cpu::ZPX, 4};
    (this -> operations)[0x6D] = {&cpu::ADC, &cpu::ABS, 4};
    (this -> operations)[0x7D] = {&cpu::ADC, &cpu::ABX, 4};
    (this -> operations)[0x79] = {&cpu::ADC, &cpu::ABY, 4};
    (this -> operations)[0x61] = {&cpu::ADC, &cpu::IDX, 6};
    (this -> operations)[0x71] = {&cpu::ADC, &cpu::IDY, 5};

    // AND
    (this -> operations)[0x29] = {&cpu::AND, &cpu::IMM, 2};
    (this -> operations)[0x25] = {&cpu::AND, &cpu::ZPG, 3};
    (this -> operations)[0x35] = {&cpu::AND, &cpu::ZPX, 4};
    (this -> operations)[0x2D] = {&cpu::AND, &cpu::ABS, 4};
    (this -> operations)[0x3D] = {&cpu::AND, &cpu::ABX, 4};
    (this -> operations)[0x39] = {&cpu::AND, &cpu::ABY, 4};
    (this -> operations)[0x21] = {&cpu::AND, &cpu::IDX, 6};
    (this -> operations)[0x31] = {&cpu::AND, &cpu::IDY, 5};

    // ASL
    (this -> operations)[0x0A] = {&cpu::ASL, &cpu::ACC, 2};
    (this -> operations)[0x06] = {&cpu::ASL, &cpu::ZPG, 5};
    (this -> operations)[0x16] = {&cpu::ASL, &cpu::ZPX, 6};
    (this -> operations)[0x0E] = {&cpu::ASL, &cpu::ABS, 6};
    (this -> operations)[0x1E] = {&cpu::ASL, &cpu::ABX, 7};

    // BCC
    (this -> operations)[0x90] = {&cpu::BCC, &cpu::REL, 2};

    // BCS
    (this -> operations)[0xB0] = {&cpu::BCS, &cpu::REL, 2};

    // BEQ
    (this -> operations)[0xF0] = {&cpu::BEQ, &cpu::REL, 2};

    // BIT
    (this -> operations)[0x24] = {&cpu::BIT, &cpu::ZPG, 3};
    (this -> operations)[0x2C] = {&cpu::BIT, &cpu::ABS, 4};

    // BMI
    (this -> operations)[0x30] = {&cpu::BMI, &cpu::REL, 2};

    // BNE
    (this -> operations)[0xD0] = {&cpu::BNE, &cpu::REL, 2};

    // BPL
    (this -> operations)[0x10] = {&cpu::BPL, &cpu::REL, 2};

    // BRK
    (this -> operations)[0x00] = {&cpu::BRK, &cpu::IMP, 7};

    // BVC
    (this -> operations)[0x50] = {&cpu::BVC, &cpu::REL, 2};

    // BVS
    (this -> operations)[0x70] = {&cpu::BVS, &cpu::REL, 2};

    // CLC
    (this -> operations)[0x18] = {&cpu::CLC, &cpu::IMP, 2};

    // CLD
    (this -> operations)[0xD8] = {&cpu::CLD, &cpu::IMP, 2};

    // CLI
    (this -> operations)[0x58] = {&cpu::CLI, &cpu::IMP, 2};

    // CLV
    (this -> operations)[0xB8] = {&cpu::CLV, &cpu::IMP, 2};

    // CMP
    (this -> operations)[0xC9] = {&cpu::CMP, &cpu::IMM, 2};
    (this -> operations)[0xC5] = {&cpu::CMP, &cpu::ZPG, 3};
    (this -> operations)[0xD5] = {&cpu::CMP, &cpu::ZPX, 4};
    (this -> operations)[0xCD] = {&cpu::CMP, &cpu::ABS, 4};
    (this -> operations)[0xDD] = {&cpu::CMP, &cpu::ABX, 4};
    (this -> operations)[0xD9] = {&cpu::CMP, &cpu::ABY, 4};
    (this -> operations)[0xC1] = {&cpu::CMP, &cpu::IDX, 6};
    (this -> operations)[0xD1] = {&cpu::CMP, &cpu::IDY, 5};

    // CPX
    (this -> operations)[0xE0] = {&cpu::CPX, &cpu::IMM, 2};
    (this -> operations)[0xE4] = {&cpu::CPX, &cpu::ZPG, 3};
    (this -> operations)[0xEC] = {&cpu::CPX, &cpu::ABS, 4};

    // CPY
    (this -> operations)[0xC0] = {&cpu::CPY, &cpu::IMM, 2};
    (this -> operations)[0xC4] = {&cpu::CPY, &cpu::ZPG, 3};
    (this -> operations)[0xCC] = {&cpu::CPY, &cpu::ABS, 4};

    // DEC
    (this -> operations)[0xC6] = {&cpu::DEC, &cpu::ZPG, 5};
    (this -> operations)[0xD6] = {&cpu::DEC, &cpu::ZPX, 6};
    (this -> operations)[0xCE] = {&cpu::DEC, &cpu::ABS, 6};
    (this -> operations)[0xDE] = {&cpu::DEC, &cpu::ABX, 7};

    // DEX
    (this -> operations)[0xCA] = {&cpu::DEX, &cpu::IMP, 2};

    // DEY
    (this -> operations)[0x88] = {&cpu::DEY, &cpu::IMP, 2};

    // EOR
    (this -> operations)[0x49] = {&cpu::EOR, &cpu::IMM, 2};
    (this -> operations)[0x45] = {&cpu::EOR, &cpu::ZPG, 3};
    (this -> operations)[0x55] = {&cpu::EOR, &cpu::ZPX, 4};
    (this -> operations)[0x4D] = {&cpu::EOR, &cpu::ABS, 4};
    (this -> operations)[0x5D] = {&cpu::EOR, &cpu::ABX, 4};
    (this -> operations)[0x59] = {&cpu::EOR, &cpu::ABY, 4};
    (this -> operations)[0x41] = {&cpu::EOR, &cpu::IDX, 6};
    (this -> operations)[0x51] = {&cpu::EOR, &cpu::IDY, 5};

    // INC
    (this -> operations)[0xE6] = {&cpu::INC, &cpu::ZPG, 5};
    (this -> operations)[0xF6] = {&cpu::INC, &cpu::ZPX, 6};
    (this -> operations)[0xEE] = {&cpu::INC, &cpu::ABS, 6};
    (this -> operations)[0xFE] = {&cpu::INC, &cpu::ABX, 7};

    // INX
    (this -> operations)[0xE8] = {&cpu::INX, &cpu::IMP, 2};

    // INY
    (this -> operations)[0xC8] = {&cpu::INY, &cpu::IMP, 2};

    // JMP
    (this -> operations)[0x4C] = {&cpu::JMP, &cpu::ABS, 3};
    (this -> operations)[0x6C] = {&cpu::JMP, &cpu::IND, 5};

    // JSR
    (this -> operations)[0x20] = {&cpu::JSR, &cpu::ABS, 6};

    // LDA
    (this -> operations)[0xA9] = {&cpu::LDA, &cpu::IMM, 2};
    (this -> operations)[0xA5] = {&cpu::LDA, &cpu::ZPG, 3};
    (this -> operations)[0xB5] = {&cpu::LDA, &cpu::ZPX, 4};
    (this -> operations)[0xAD] = {&cpu::LDA, &cpu::ABS, 4};
    (this -> operations)[0xBD] = {&cpu::LDA, &cpu::ABX, 4};
    (this -> operations)[0xB9] = {&cpu::LDA, &cpu::ABY, 4};
    (this -> operations)[0xA1] = {&cpu::LDA, &cpu::IDX, 6};
    (this -> operations)[0xB1] = {&cpu::LDA, &cpu::IDY, 5};

    // LDX
    (this -> operations)[0xA2] = {&cpu::LDX, &cpu::IMM, 2};
    (this -> operations)[0xA6] = {&cpu::LDX, &cpu::ZPG, 3};
    (this -> operations)[0xB6] = {&cpu::LDX, &cpu::ZPY, 4};
    (this -> operations)[0xAE] = {&cpu::LDX, &cpu::ABS, 4};
    (this -> operations)[0xBE] = {&cpu::LDX, &cpu::IDY, 4};

    // LDY
    (this -> operations)[0xA0] = {&cpu::LDY, &cpu::IMM, 2};
    (this -> operations)[0xA4] = {&cpu::LDY, &cpu::ZPG, 3};
    (this -> operations)[0xB4] = {&cpu::LDY, &cpu::ZPX, 4};
    (this -> operations)[0xAC] = {&cpu::LDY, &cpu::ABS, 4};
    (this -> operations)[0xBC] = {&cpu::LDY, &cpu::IDX, 4};

    // LSR
    (this -> operations)[0x4A] = {&cpu::LSR, &cpu::ACC, 2};
    (this -> operations)[0x46] = {&cpu::LSR, &cpu::ZPG, 5};
    (this -> operations)[0x56] = {&cpu::LSR, &cpu::ZPX, 6};
    (this -> operations)[0x4E] = {&cpu::LSR, &cpu::ABS, 6};
    (this -> operations)[0x5E] = {&cpu::LSR, &cpu::ABX, 7};

    // NOP
    (this -> operations)[0xEA] = {&cpu::NOP, &cpu::IMP, 2};

    // ORA
    (this -> operations)[0x09] = {&cpu::ORA, &cpu::IMM, 2};
    (this -> operations)[0x05] = {&cpu::ORA, &cpu::ZPG, 3};
    (this -> operations)[0x15] = {&cpu::ORA, &cpu::ZPX, 4};
    (this -> operations)[0x0D] = {&cpu::ORA, &cpu::ABS, 4};
    (this -> operations)[0x1D] = {&cpu::ORA, &cpu::ABX, 4};
    (this -> operations)[0x19] = {&cpu::ORA, &cpu::ABY, 4};
    (this -> operations)[0x01] = {&cpu::ORA, &cpu::IDX, 6};
    (this -> operations)[0x11] = {&cpu::ORA, &cpu::IDY, 5};

    // PHA
    (this -> operations)[0x48] = {&cpu::PHA, &cpu::IMP, 3};

    // PHP
    (this -> operations)[0x08] = {&cpu::PHP, &cpu::IMP, 3};

    // PLA
    (this -> operations)[0x68] = {&cpu::PLA, &cpu::IMP, 4};

    // PLP
    (this -> operations)[0x28] = {&cpu::PLP, &cpu::IMP, 4};

    // ROL
    (this -> operations)[0x2A] = {&cpu::ROL, &cpu::ACC, 2};
    (this -> operations)[0x26] = {&cpu::ROL, &cpu::ZPG, 5};
    (this -> operations)[0x36] = {&cpu::ROL, &cpu::ZPX, 6};
    (this -> operations)[0x2E] = {&cpu::ROL, &cpu::ABS, 6};
    (this -> operations)[0x3E] = {&cpu::ROL, &cpu::ABX, 7};

    // ROR
    (this -> operations)[0x6A] = {&cpu::ROR, &cpu::ACC, 2};
    (this -> operations)[0x66] = {&cpu::ROR, &cpu::ZPG, 5};
    (this -> operations)[0x76] = {&cpu::ROR, &cpu::ZPX, 6};
    (this -> operations)[0x6E] = {&cpu::ROR, &cpu::ABS, 6};
    (this -> operations)[0x7E] = {&cpu::ROR, &cpu::ABX, 7};

    // RTI
    (this -> operations)[0x40] = {&cpu::RTI, &cpu::IMP, 6};

    // RTS
    (this -> operations)[0x60] = {&cpu::RTS, &cpu::IMP, 6};

    // SBC
    (this -> operations)[0xE9] = {&cpu::SBC, &cpu::IMM, 2};
    (this -> operations)[0xE5] = {&cpu::SBC, &cpu::ZPG, 3};
    (this -> operations)[0xF5] = {&cpu::SBC, &cpu::ZPX, 4};
    (this -> operations)[0xED] = {&cpu::SBC, &cpu::ABS, 4};
    (this -> operations)[0xFD] = {&cpu::SBC, &cpu::ABX, 4};
    (this -> operations)[0xF9] = {&cpu::SBC, &cpu::ABY, 4};
    (this -> operations)[0xE1] = {&cpu::SBC, &cpu::IDX, 6};
    (this -> operations)[0xF1] = {&cpu::SBC, &cpu::IDY, 5};

    // SEC
    (this -> operations)[0x38] = {&cpu::SEC, &cpu::IMP, 2};

    // SED
    (this -> operations)[0xF8] = {&cpu::SED, &cpu::IMP, 2};

    // SEI
    (this -> operations)[0x78] = {&cpu::SEI, &cpu::IMP, 2};

    // STA
    (this -> operations)[0x85] = {&cpu::STA, &cpu::ZPG, 3};
    (this -> operations)[0x95] = {&cpu::STA, &cpu::ZPX, 4};
    (this -> operations)[0x8D] = {&cpu::STA, &cpu::ABS, 4};
    (this -> operations)[0x9D] = {&cpu::STA, &cpu::ABX, 5};
    (this -> operations)[0x99] = {&cpu::STA, &cpu::ABY, 5};
    (this -> operations)[0x81] = {&cpu::STA, &cpu::IDX, 6};
    (this -> operations)[0x91] = {&cpu::STA, &cpu::IDY, 6};

    // STX
    (this -> operations)[0x86] = {&cpu::STX, &cpu::ZPG, 3};
    (this -> operations)[0x96] = {&cpu::STX, &cpu::ZPY, 4};
    (this -> operations)[0x8E] = {&cpu::STX, &cpu::ABS, 4};

    // STY
    (this -> operations)[0x84] = {&cpu::STY, &cpu::ZPG, 3};
    (this -> operations)[0x94] = {&cpu::STY, &cpu::ZPX, 4};
    (this -> operations)[0x8C] = {&cpu::STY, &cpu::ABS, 4};

    // TAX
    (this -> operations)[0xAA] = {&cpu::TAX, &cpu::IMP, 2};

    // TAY
    (this -> operations)[0xA8] = {&cpu::TAY, &cpu::IMP, 2};

    // TSX
    (this -> operations)[0xBA] = {&cpu::TSX, &cpu::IMP, 2};

    // TXA
    (this -> operations)[0x8A] = {&cpu::TXA, &cpu::IMP, 2};

    // TXS
    (this -> operations)[0x9A] = {&cpu::TXS, &cpu::IMP, 2};

    // TYA
    (this -> operations)[0x98] = {&cpu::TYA, &cpu::IMP, 2};
}

uint8_t cpu::ADC ()
{
    uint8_t  input_data  = this -> get_input_data ();
    uint16_t result;
    uint8_t  overflow;

    result   = this -> accumulator + input_data + this -> get_flag (cpu::F_CARRY);
    overflow = ~((uint16_t) this -> accumulator ^ (uint16_t) input_data);
    overflow &= (uint16_t) this -> accumulator ^ (uint16_t) result;
    overflow >>= 7;

    this -> set_flag (cpu::F_CARRY, result >> 8);
    this -> set_flag (cpu::F_OVERFLOW, overflow);
    this -> set_flag (cpu::F_ZERO, (result & 0x00FF) == 0);
    this -> set_flag (cpu::F_NEGATIVE, (result & 0x00FF) >> 7);

    this -> accumulator = (result & 0x00FF);

    return (0);
}

uint8_t cpu::AND ()
{
    uint8_t input_data = this -> get_input_data ();

    this -> accumulator &= input_data;
    this -> set_flag (cpu::F_ZERO, this -> accumulator == 0);
    this -> set_flag (cpu::F_NEGATIVE, this -> accumulator & 0x80);

    return (0);
}

uint8_t cpu::ASL ()
{
    uint8_t input_data = this -> get_input_data ();

    this -> set_flag (cpu::F_CARRY, input_data >> 7);
    input_data <<= 1;
    if (this -> accumulator_addressing)
        this -> accumulator = input_data;
    else
        this -> write (this -> destination_address, input_data);
    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);

    return (0);
}

uint8_t cpu::BCC ()
{
    uint8_t additional_cycles = 0;

    if (this -> get_flag (cpu::F_CARRY) == 0)
    {
        additional_cycles++;
        if ((this -> program_counter & 0xFF00) !=
           ((this -> program_counter + this -> jump_relative_address) & 0xFF00))
            additional_cycles++;
        this -> program_counter += this -> jump_relative_address;
    }

    return (additional_cycles);
}

uint8_t cpu::BCS ()
{
    uint8_t additional_cycles = 0;

    if (this -> get_flag (cpu::F_CARRY) == 1)
    {
        additional_cycles++;
        if ((this -> program_counter & 0xFF00) !=
            ((this -> program_counter + this -> jump_relative_address) & 0xFF00))
            additional_cycles++;
        this -> program_counter += this -> jump_relative_address;
    }

    return (additional_cycles);
}

uint8_t cpu::BEQ ()
{
    uint8_t additional_cycles = 0;

    if (this -> get_flag (cpu::F_ZERO) == 1)
    {
        additional_cycles++;
        if ((this -> program_counter & 0xFF00) !=
            ((this -> program_counter + this -> jump_relative_address) & 0xFF00))
            additional_cycles++;
        this -> program_counter += this -> jump_relative_address;
    }

    return (additional_cycles);
}

uint8_t cpu::BIT ()
{
    uint8_t input_data = this -> get_input_data ();
    uint8_t result     = input_data & this -> accumulator;

    this -> set_flag (cpu::F_ZERO, result == 0);
    this -> set_flag (cpu::F_OVERFLOW, (result & ( 1 << 6 )) >> 6);
    this -> set_flag (cpu::F_NEGATIVE, result >> 7);

    return (0);
}

uint8_t cpu::BMI ()
{
    uint8_t additional_cycles = 0;

    if (this -> get_flag (cpu::F_NEGATIVE) == 1)
    {
        additional_cycles++;
        if ((this -> program_counter & 0xFF00) !=
            ((this -> program_counter + this -> jump_relative_address) & 0xFF00))
            additional_cycles++;
        this -> program_counter += this -> jump_relative_address;
    }

    return (additional_cycles);
}

uint8_t cpu::BNE ()
{
    uint8_t additional_cycles = 0;

    if (this -> get_flag (cpu::F_ZERO) == 0)
    {
        additional_cycles++;
        if ((this -> program_counter & 0xFF00) !=
            ((this -> program_counter + this -> jump_relative_address) & 0xFF00))
            additional_cycles++;
        this -> program_counter += this -> jump_relative_address;
    }

    return (additional_cycles);
}

uint8_t cpu::BPL ()
{
    uint8_t additional_cycles = 0;

    if (this -> get_flag (cpu::F_NEGATIVE) == 0)
    {
        additional_cycles++;
        if ((this -> program_counter & 0xFF00) !=
            ((this -> program_counter + this -> jump_relative_address) & 0xFF00))
            additional_cycles++;
        this -> program_counter += this -> jump_relative_address;
    }

    return (additional_cycles);
}

uint8_t cpu::BRK ()
{
    uint8_t pc_low_byte      = this -> program_counter & 0x00FF;
    uint8_t pc_high_byte     = (this -> program_counter >> 8) & 0x00FF;
    uint8_t pc_new_low_byte  = this -> read (0xFFFF);
    uint8_t pc_new_high_byte = this -> read (0xFFFE);

    this -> set_flag (F_BREAK, 1);
    this -> push_to_stack (pc_high_byte);
    this -> push_to_stack (pc_low_byte);
    this -> push_to_stack (this -> flags_register);
    this -> program_counter = ((uint16_t) pc_new_low_byte) & 0x00FF;
    this -> program_counter += (uint16_t) pc_new_high_byte << 8;

    return (0);
}

uint8_t cpu::BVC ()
{
    uint8_t additional_cycles = 0;

    if (this -> get_flag (cpu::F_OVERFLOW) == 0)
    {
        additional_cycles++;
        if (this -> program_counter >> 8 !=
            (this -> program_counter + this -> jump_relative_address) >> 8)
            additional_cycles++;
        this -> program_counter += this -> jump_relative_address;
    }

    return (additional_cycles);
}

uint8_t cpu::BVS ()
{
    uint8_t additional_cycles = 0;

    if (this -> get_flag (cpu::F_OVERFLOW) == 1)
    {
        additional_cycles++;
        if (this -> program_counter >> 8 !=
            (this -> program_counter + this -> jump_relative_address) >> 8)
            additional_cycles++;
        this -> program_counter += this -> jump_relative_address;
    }

    return (additional_cycles);
}

uint8_t cpu::CLC ()
{
    this -> set_flag (cpu::F_CARRY, 0);

    return (0);
}

uint8_t cpu::CLD ()
{
    this -> set_flag (cpu::F_DECIMAL, 0);

    return (0);
}

uint8_t cpu::CLI ()
{
    this -> set_flag (cpu::F_INTERRUPT_DISABLE, 0);

    return (0);
}

uint8_t cpu::CLV ()
{
    this -> set_flag (cpu::F_OVERFLOW, 0);

    return (0);
}

uint8_t cpu::CMP ()
{
    uint8_t input_data = this -> get_input_data ();
    auto diff          = ((uint16_t) this -> accumulator) - (uint16_t) input_data;

    this -> set_flag (cpu::F_CARRY, this -> accumulator >= input_data);
    this -> set_flag (cpu::F_ZERO, this -> accumulator == input_data);
    this -> set_flag (cpu::F_NEGATIVE, diff >> 7);

    return (0);
}

uint8_t cpu::CPX ()
{
    uint8_t input_data = this -> get_input_data ();
    auto diff          = (uint16_t) this -> x_register - (uint16_t) input_data;

    this -> set_flag (cpu::F_CARRY, this -> x_register >= input_data);
    this -> set_flag (cpu::F_ZERO, this -> x_register == input_data);
    this -> set_flag (cpu::F_NEGATIVE, diff >> 7);

    return (0);
}

uint8_t cpu::CPY ()
{
    uint8_t input_data = this -> get_input_data ();
    auto diff          = (uint16_t) this -> y_register - (uint16_t) input_data;

    this -> set_flag (cpu::F_CARRY, this -> y_register >= input_data);
    this -> set_flag (cpu::F_ZERO, this -> y_register == input_data);
    this -> set_flag (cpu::F_NEGATIVE, diff >> 7);

    return (0);
}

uint8_t cpu::DEC ()
{
    uint8_t input_data = this -> get_input_data () - 1;

    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);
    this -> write (this -> destination_address, input_data);

    return (0);
}

uint8_t cpu::DEX ()
{
    this -> x_register -= 1;
    this -> set_flag (cpu::F_ZERO, this -> x_register == 0);
    this -> set_flag (cpu::F_NEGATIVE, this -> x_register >> 7);

    return (0);
}

uint8_t cpu::DEY ()
{
    this -> y_register -= 1;
    this -> set_flag (cpu::F_ZERO, this -> y_register == 0);
    this -> set_flag (cpu::F_NEGATIVE, this -> y_register >> 7);

    return (0);
}

uint8_t cpu::EOR ()
{
    uint8_t input_data = this -> get_input_data ();

    this -> accumulator ^= input_data;
    this -> set_flag (cpu::F_ZERO, this -> accumulator == 0);
    this -> set_flag (cpu::F_NEGATIVE, this -> accumulator >> 7);

    return (0);
}

uint8_t cpu::INC ()
{
    uint8_t input_data = this -> get_input_data () + 1;

    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);
    this -> write (this -> destination_address, input_data);

    return (0);
}

uint8_t cpu::INX ()
{
    this -> x_register += 1;
    this -> set_flag (cpu::F_ZERO, this -> x_register == 0);
    this -> set_flag (cpu::F_NEGATIVE, this -> x_register >> 7);

    return (0);
}

uint8_t cpu::INY ()
{
    this -> y_register += 1;
    this -> set_flag (cpu::F_ZERO, this -> y_register == 0);
    this -> set_flag (cpu::F_NEGATIVE, this -> y_register >> 7);

    return (0);
}

uint8_t cpu::JMP ()
{
    this -> program_counter = this -> destination_address;

    return (0);
}

uint8_t cpu::JSR ()
{
    uint8_t high_byte = ((this -> program_counter)) >> 8;
    uint8_t low_byte  = ((this -> program_counter)) & 0x00FF;

    this -> push_to_stack (high_byte);
    this -> push_to_stack (low_byte);

    this -> program_counter = this -> destination_address;

    return (0);
}

uint8_t cpu::LDA ()
{
    uint8_t input_data  = this -> get_input_data ();

    this -> accumulator = input_data;
    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);

    return (0);
}

uint8_t cpu::LDX ()
{
    uint8_t input_data = this -> get_input_data ();

    this -> x_register = input_data;
    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);

    return (0);
}

uint8_t cpu::LDY ()
{
    uint8_t input_data = this -> get_input_data ();

    this -> y_register = input_data;
    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);

    return (0);
}

uint8_t cpu::LSR ()
{
    uint8_t input_data = this -> get_input_data ();

    this -> set_flag (cpu::F_CARRY, input_data & 0b00000001);
    input_data >>= 1;
    if (this -> accumulator_addressing)
        this -> accumulator = input_data;
    else
        this -> write (this -> destination_address, input_data);
    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);

    return (0);
}

uint8_t cpu::NOP () // NOLINT
{
    return (0);
}

uint8_t cpu::ORA ()
{
    uint8_t input_data  = this -> get_input_data ();

    this -> accumulator |= input_data;
    this -> set_flag (cpu::F_ZERO, this -> accumulator == 0);
    this -> set_flag (cpu::F_NEGATIVE, this -> accumulator >> 7);

    return (0);
}

uint8_t cpu::PHA ()
{
    this -> push_to_stack (this -> accumulator);

    return (0);
}

uint8_t cpu::PHP ()
{
    this -> push_to_stack (this -> flags_register);

    return (0);
}

uint8_t cpu::PLA ()
{
    this -> accumulator = this -> pull_from_stack ();
    this -> set_flag (cpu::F_ZERO, this -> accumulator == 0);
    this -> set_flag (cpu::F_NEGATIVE, (this -> accumulator >> 7));

    return (0);
}

uint8_t cpu::PLP ()
{
    this -> flags_register = this -> pull_from_stack ();

    return (0);
}

uint8_t cpu::ROL ()
{
    uint8_t input_data = this -> get_input_data ();
    uint8_t old_carry  = this -> get_flag (cpu::F_CARRY);

    this -> set_flag (cpu::F_CARRY, input_data >> 7);
    input_data <<= 1;
    input_data += old_carry;
    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);

    if (this -> accumulator_addressing)
        this -> accumulator = input_data;
    else
        this -> write (this -> destination_address, input_data);

    return (0);
}

uint8_t cpu::ROR ()
{
    uint8_t input_data = this -> get_input_data ();
    uint8_t old_carry  = this -> get_flag (cpu::F_CARRY);

    this -> set_flag (cpu::F_CARRY, input_data & 0b00000001);
    input_data  >>= 1;
    input_data  += (old_carry << 7);
    this -> set_flag (cpu::F_ZERO, input_data == 0);
    this -> set_flag (cpu::F_NEGATIVE, input_data >> 7);

    if (this -> accumulator_addressing)
        this -> accumulator = input_data;
    else
        this -> write (this -> destination_address, input_data);

    return (0);
}

uint8_t cpu::RTI ()
{
    this -> flags_register = pull_from_stack();
    uint8_t pc_low_byte    = pull_from_stack();
    uint8_t pc_high_byte   = pull_from_stack();

    this -> program_counter = (((uint16_t) pc_high_byte) << 8) + pc_low_byte;
    this -> set_flag (cpu::F_BREAK, 0);

    return (0);
}

uint8_t cpu::RTS ()
{
    uint8_t low_byte  = this -> pull_from_stack ();
    uint8_t high_byte = this -> pull_from_stack ();

    this -> program_counter = ((uint16_t) high_byte << 8) + low_byte;

    return (0);
}

uint8_t cpu::SBC ()
{
    uint16_t    inverted_input;
    uint8_t     input_data     = this -> get_input_data ();
    uint16_t    result;
    uint16_t    overflow;

    inverted_input = ((uint16_t) input_data) ^ 0x00FF;
    result         = ((uint16_t) this -> accumulator) + inverted_input;
    result         += (uint16_t) this -> get_flag (cpu::F_CARRY);
    overflow       = result ^ ((uint16_t) this -> accumulator);
    overflow       &= result ^ inverted_input;
    overflow       >>= 7;

    this -> set_flag (cpu::F_CARRY, result >> 8);
    this -> set_flag (cpu::F_ZERO, (result & 0x00FF) == 0);
    this -> set_flag (cpu::F_OVERFLOW, overflow);
    this -> set_flag (cpu::F_NEGATIVE, (result & 0x00FF) >> 7);

    this -> accumulator = (result & 0x00FF);

    return (0);
}

uint8_t cpu::SEC ()
{
    this -> set_flag (cpu::F_CARRY, 1);

    return (0);
}

uint8_t cpu::SED ()
{
    this -> set_flag (cpu::F_DECIMAL, 1);

    return (0);
}

uint8_t cpu::SEI ()
{
    this -> set_flag (cpu::F_INTERRUPT_DISABLE, 1);

    return (0);
}

uint8_t cpu::STA ()
{
    this -> write (this -> destination_address, this -> accumulator);

    return (0);
}

uint8_t cpu::STX ()
{
    this -> write (this -> destination_address, this -> x_register);

    return (0);
}

uint8_t cpu::STY ()
{
    this -> write (this -> destination_address, this -> y_register);

    return (0);
}

uint8_t cpu::TAX ()
{
    this -> x_register  = this -> accumulator;
    this -> set_flag (cpu::F_ZERO, this -> x_register == 0);
    this -> set_flag (cpu::F_ZERO, this -> x_register >> 7);

    return (0);
}

uint8_t cpu::TAY ()
{
    this -> y_register  = this -> accumulator;
    this -> set_flag (cpu::F_ZERO, this -> y_register == 0);
    this -> set_flag (cpu::F_ZERO, this -> y_register >> 7);

    return (0);
}

uint8_t cpu::TSX ()
{
    this -> x_register  = this -> stack_pointer;
    this -> set_flag (cpu::F_ZERO, this -> x_register == 0);
    this -> set_flag (cpu::F_ZERO, this -> x_register >> 7);

    return (0);
}

uint8_t cpu::TXA ()
{
    this -> accumulator = this -> x_register;
    this -> set_flag (cpu::F_ZERO, this -> x_register == 0);
    this -> set_flag (cpu::F_ZERO, this -> x_register >> 7);

    return (0);
}

uint8_t cpu::TXS ()
{
    this -> stack_pointer   = this -> x_register;

    return (0);
}

uint8_t cpu::TYA ()
{
    this -> accumulator = this -> y_register;
    this -> set_flag (cpu::F_ZERO, this -> y_register == 0);
    this -> set_flag (cpu::F_ZERO, this -> y_register >> 7);

    return (0);
}

uint8_t cpu::UNK () // NOLINT
{
    return (0);
}