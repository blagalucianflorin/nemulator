#include <iostream>
#include <vector>
#include <cstdlib>

#include <random>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "include/bus/bus.h"
#include "include/devices/memories/ram.h"
#include "include/devices/memories/ppu_nametable_ram.h"
#include "include/devices/memories/ppu_palette_ram.h"
#include "include/devices/cpu/6502.h"
#include "include/devices/ppu/ppu.h"
#include "include/devices/cartridges/cartridge.h"
#include "debugging/6502debugger.h"
#include "include/devices/ppu/oam.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600

TTF_Font *open_font (const char *font_path)
{
    TTF_Font *font = TTF_OpenFont (font_path, 24);
    if (font == nullptr)
    {
        std::cout << "error: font not found" << std::endl;
        exit (EXIT_FAILURE);
    }

    return (font);
}

void ToggleFullscreen(SDL_Window* Window)
{
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
    SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);
}

void main_window (SDL_Window *&window, SDL_Renderer *&renderer, const char *window_title)
{
    SDL_Init (SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer (WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle (window, window_title);
    TTF_Init();
}

void draw_tiles (SDL_Renderer *renderer, cartridge *my_cartridge)
{
    uint8_t tile[8][8];

    int top = 10;
    int left = 810;

    std::map <int, std::vector <int>> palette =
    {
        {0, {0, 0, 0}},
        {1, {255, 0, 0}},
        {2, {0, 255, 0}},
        {3, {0, 0, 255}},
    };

    int new_row = 0;
    for (int i = 0; i < 512; i++) {
        uint16_t start = (i * 16);

        for (uint8_t j = 0; j < 8; j++) {
            uint8_t low = my_cartridge -> read(start + j);
            uint8_t high = my_cartridge -> read(start + j + 8);

            for (uint8_t k = 0; k < 8; k++) {
                tile[j][7 - k] = (high & 0b00000001) + (low & 0b00000001);
                low >>= 1;
                high >>= 1;
            }
        }

        for (int m = 7; m >= 0; m--) {
            for (int n = 7; n >= 0; n--) {
                SDL_SetRenderDrawColor(renderer, palette[tile[m][n]][0],
                                       palette[tile[m][n]][1],
                                       palette[tile[m][n]][2], 0);

                SDL_RenderDrawPoint(renderer, left + n, top + m);
            }
        }

        left += 8;
        new_row++;
        if (new_row == 16)
        {
            top += 8;
            new_row = 0;
            left = 810;
        }
    }
}

int main (int argc, char **argv)
{
    auto         last_coords   = new t_coords;
    SDL_Event    event;
    SDL_Renderer *renderer;
    SDL_Window   *window;
    TTF_Font     *font;
    t_cpu_drawer cpu_drawer {};
    int          quit;

    main_window (window, renderer, "6502 Monitor");
    font = open_font ("fonts/Roboto_Mono/RobotoMono-Medium.ttf");

    auto nes_cpu_bus           = new bus (0x0000, 0xFFFF);
    auto nes_cpu               = new cpu ();
    auto nes_cpu_ram           = new ram ();
    auto nes_ppu_bus           = new bus (0x0000, 0x3FFF);
    auto nes_ppu_oam           = new oam ();
    auto nes_ppu               = new ppu (renderer);
    auto nes_ppu_nametable_ram = new ppu_nametable_ram ();
    auto nes_ppu_palette_ram   = new ppu_palette_ram ();
//    auto nes_cpu_cartridge     = new cartridge ("../testing/devices/cartridges/roms/ines/trainer_content.ines");
//    auto nes_ppu_cartridge     = new cartridge ("../testing/devices/cartridges/roms/ines/trainer_content.ines");
//    auto nes_cpu_cartridge     = new cartridge ("../roms/pacman.ines");
//    auto nes_ppu_cartridge     = new cartridge ("../roms/pacman.ines");
//    auto nes_cpu_cartridge     = new cartridge ("../roms/smb3.ines");
//    auto nes_ppu_cartridge     = new cartridge ("../roms/smb3.ines");
    auto nes_cpu_cartridge     = new cartridge ("../roms/smb.ines");
    auto nes_ppu_cartridge     = new cartridge ("../roms/smb.ines");
//    auto nes_cpu_cartridge     = new cartridge ("../roms/nestest.ines");
//    auto nes_ppu_cartridge     = new cartridge ("../roms/nestest.ines");

    nes_ppu -> attach (nes_cpu);
    nes_ppu -> attach (nes_ppu_oam);
    nes_ppu_oam -> attach (nes_cpu);
    nes_ppu_oam -> attach (nes_ppu);
    nes_cpu_bus -> add_device (nes_cpu);
    nes_cpu_bus -> add_device (nes_cpu_ram);
    nes_cpu_bus -> add_device (nes_cpu_cartridge);
    nes_cpu_bus -> add_device (nes_ppu);
    nes_cpu_bus -> add_device (nes_ppu_oam);
    nes_ppu_cartridge -> set_lower_bound (0x0000);
    nes_ppu_cartridge -> set_upper_bound (0x1FFF);
    nes_ppu_bus -> add_device (nes_ppu_cartridge);
    nes_ppu_bus -> add_device (nes_ppu_nametable_ram);
    nes_ppu_bus -> add_device (nes_ppu_palette_ram);
    nes_ppu     -> set_child_bus (*nes_ppu_bus);

//    nes_ppu -> set_control_flag (ppu::F_ADDRESS_INCREMENT, true);

    nes_cpu -> reset ();

//    code_injector ("code.txt", 0x0000, nes_cpu);
//    nes_cpu -> set_flag (cpu::F_CARRY, 1);

    cpu_drawer.my_cpu   = nes_cpu;
    cpu_drawer.renderer = renderer;
    cpu_drawer.font     = font;


//    nes_cpu -> write (0x4014, 0x00);

    nes_cpu -> reset ();
//    nes_cpu -> program_counter = 0xC000;
    nes_cpu -> cycles_elapsed = 7;

    quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event) == 1)
            if (event.type == SDL_QUIT)
                quit = 1;
            else if(event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == ' ')
                    nes_cpu -> step ();

                if (event.key.keysym.sym  == SDLK_f)
                    ToggleFullscreen(window);
            }


        if (nes_cpu -> program_counter == 50798)
            quit = 1;

        // Render white background
        SDL_SetRenderDrawColor (renderer, 255, 255, 255, 0);
        SDL_RenderClear (renderer);


        *last_coords = render_cpu (cpu_drawer, 15, 15);

        *last_coords = render_text (cpu_drawer, "ZERO PAGE:", 16, last_coords -> y + last_coords -> h + 50,
                                    {0, 0, 0, 0});
        *last_coords = render_memory (cpu_drawer, 15,last_coords -> y + last_coords -> h,0x0000, 2, true);

        *last_coords = render_text (cpu_drawer, "STACK:", 16,last_coords -> y + last_coords -> h + 50,{0, 0, 0, 0});
        *last_coords = render_memory (cpu_drawer, 15,last_coords -> y + last_coords -> h,0x01E0, 2, false);

        *last_coords = render_text (cpu_drawer, "PROGRAM COUNTER MEMORY:", 16,last_coords -> y + last_coords -> h + 50,{0, 0, 0, 0});
        *last_coords = render_memory (cpu_drawer, 15,last_coords -> y + last_coords -> h,nes_cpu -> program_counter & 0xFFF0, 2, true);

        draw_tiles (renderer, nes_cpu_cartridge);

//        for (int i = 0; i < 89342; i++)
//            nes_ppu -> clock ();

//        nes_cpu -> step ();
//        nes_cpu -> clock ();
//        nes_ppu -> clock ();
//        nes_ppu -> clock ();
//        nes_ppu -> clock ();

        SDL_RenderPresent(renderer);
    }

//    while (nes_cpu -> program_counter != 50798)
//    {
//        nes_cpu -> clock ();
//        nes_ppu -> clock ();
//        nes_ppu -> clock ();
//        nes_ppu -> clock ();
//    }
//    nes_cpu -> step ();
//    nes_cpu -> clock ();

    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
