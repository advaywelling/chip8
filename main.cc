#include <iostream>
#include <stdlib.h>
#include "chip8.h"

int main() {
    chip8 cpu{};

    cpu.load_rom("ROMS/Chip8 Picture.ch8");
    for(int i{}; i < 20; i++) {
        std::cout << "Current PC: " << cpu.get_pc() << "\n";
        cpu.cycle();
    }
}
