//
// Created by lblaga on 12.03.2021.
//

#ifndef NEMULATOR_6502DEBUGGER_H
#define NEMULATOR_6502DEBUGGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "include/bus/bus.h"
#include "include/devices/memories/memory.h"
#include "include/devices/cpu/6502.h"

struct t_coords
{
    int x;
    int y;
    int w;
    int h;
};

struct t_cpu_drawer
{
    cpu          *my_cpu;
    SDL_Renderer *renderer;
    TTF_Font     *font;
};

/* CPU manipulation */
void code_injector (const char *file_name, uint16_t start_address, cpu *my_cpu);

/* Console printing */
void print_memory (cpu *my_cpu, uint16_t start, uint16_t lines);

void print_cpu (cpu *my_cpu, uint8_t zpg_lines, uint8_t stk_lines);

/* SDL2 printing */
t_coords render_text (t_cpu_drawer cpu_drawer, const char *text, int x, int y, SDL_Color color);

t_coords render_cpu (t_cpu_drawer cpu_drawer, int x, int y);

t_coords render_memory (t_cpu_drawer cpu_drawer, int x, int y, uint16_t start_address, uint16_t lines,
                        bool pc_highlight);

std::string to_hexa (int number, int width, bool hex_prefix = false);

#endif //NEMULATOR_6502DEBUGGER_H
