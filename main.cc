#include "chip8.h"
#include "display.h"
#include <SDL.h>

int main() {
    chip8 cpu{};

    if (!cpu.load_rom("ROMS/Pong [Paul Vervalin, 1990].ch8")) {
        return 1;
    }
    Display display("Chip8", 640, 320);

    bool keys[16] = {false};
    const int CYCLES_PER_FRAME = 10;

    bool quit = false;
    while (!quit) {
        quit = display.input(keys);
        cpu.set_keys(keys);
        
        for (int i{}; i < CYCLES_PER_FRAME; i++) {
            cpu.cycle();
        }
        cpu.tick_timers();

        display.update(cpu.get_display());
        SDL_Delay(16);
    }
    return 0;
}
