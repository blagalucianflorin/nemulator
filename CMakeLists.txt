cmake_minimum_required(VERSION 3.17)
project(nemulator)
set(CMAKE_CXX_STANDARD 17)

include_directories (${PROJECT_SOURCE_DIR})

set (SOURCES
    src/bus/bus.cpp
    src/devices/cpu/6502/6502.cpp
    src/devices/cpu/6502/6502_addressing_modes.cpp
    src/devices/cpu/6502/6502_instructions.cpp
    src/devices/memories/memory.cpp
    src/devices/device.cpp
    debugging/6502debugger.cpp
    src/devices/memories/ram.cpp
    src/devices/cartridges/cartridge.cpp
    src/devices/cartridges/read_ines.cpp
    src/devices/ppu/ppu.cpp
    src/devices/memories/ppu_palette_ram.cpp
    src/devices/memories/ppu_nametable_ram.cpp
    src/devices/ppu/oam.cpp)

set (INCLUDES
    include/bus/bus.h
    include/devices/cpu/6502.h
    include/devices/device.h
    include/devices/memories/memory.h
    include/forwards/classes.h
    include/misc/macros.h
    debugging/6502debugger.h
    include/devices/memories/ram.h
    include/devices/cartridges/cartridge.h
    include/devices/cartridges/exceptions/cartridge_exception.h
    include/devices/ppu/ppu.h
    include/devices/ppu/exceptions/ppu_exception.h
    include/devices/memories/ppu_palette_ram.h
    include/devices/memories/ppu_nametable_ram.h
    include/devices/ppu/oam.h)

set (TESTS
    testing/devices/cpu/6502/addressing_modes/addressing_modes.h
    testing/devices/cpu/6502/addressing_modes/addressing_modes.cpp

    testing/devices/cpu/6502/instructions/instructions.h

    testing/devices/cpu/6502/instructions/arithmetic.h
    testing/devices/cpu/6502/instructions/arithmetic.cpp

    testing/devices/cpu/6502/instructions/load_store.h
    testing/devices/cpu/6502/instructions/load_store.cpp

    testing/devices/cpu/6502/instructions/transfer.h
    testing/devices/cpu/6502/instructions/transfer.cpp

    testing/devices/cpu/6502/instructions/stack.h
    testing/devices/cpu/6502/instructions/stack.cpp

    testing/devices/cpu/6502/instructions/logical.h
    testing/devices/cpu/6502/instructions/logical.cpp

    testing/devices/cpu/6502/instructions/jump.h
    testing/devices/cpu/6502/instructions/jump.cpp

    testing/devices/cpu/6502/instructions/branch.h
    testing/devices/cpu/6502/instructions/branch.cpp

    testing/devices/cpu/6502/instructions/status.h
    testing/devices/cpu/6502/instructions/status.cpp

    testing/devices/cpu/6502/instructions/system.h
    testing/devices/cpu/6502/instructions/system.cpp

    testing/devices/cpu/6502/instructions/increments_decrements.h
    testing/devices/cpu/6502/instructions/increments_decrements.cpp

    testing/devices/cpu/6502/instructions/shifts.h
    testing/devices/cpu/6502/instructions/shifts.cpp

    testing/devices/cartridges/cartridge.h
    testing/devices/cartridges/cartridge.cpp

    testing/devices/ppu/ppu.h
    testing/devices/ppu/ppu.cpp)

add_executable (nemulator main.cpp ${SOURCES} ${INCLUDES})

# Link SDL2 to main executable
target_link_libraries(nemulator -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf)

add_executable (nemulator-tests testing/main-testing.cpp ${SOURCES} ${TESTS}
                ${INCLUDES})

# Link SDL2 to tests
target_link_libraries(nemulator-tests -lSDL2 -lSDL2_mixer -lSDL2_image
                      -lSDL2_ttf)

# Define G_TESTING at compile time for tests executable
target_compile_definitions (nemulator-tests PUBLIC G_TESTING)

target_compile_definitions (nemulator PUBLIC G_TESTING)

# Include and link GTEST
add_subdirectory (lib/googletest-master)
include_directories (lib/googletest-master/googletest/include)
include_directories (lib/googletest-master/googlemock/include)
target_link_libraries(nemulator-tests gtest gtest_main gmock)