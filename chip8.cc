#include "chip8.h"
#include <fstream>
#include <iostream> 
#include <cstring> 
#include <random>

chip8::chip8() : rng(std::random_device{}()){
    pc = 0x200;
    static const uint8_t font[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	    0x20, 0x60, 0x20, 0x20, 0x70, // 1
	    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    for(int i{}; i < 80; i++) {
        mem[0x50 + i] = font[i];
    }
}

bool chip8::load_rom(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return false;
    }
    std::streamsize size = file.tellg();
    if ((4096 - 0x200) < size) {
        std::cerr << filename << " too big\n";
        return false;
    }
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(mem + 0x200), size);
    return true;
}

void chip8::cycle() {
    uint16_t opcode = (mem[pc] << 8) | mem[pc + 1];

    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t kk = opcode & 0x00FF;
    uint8_t n = opcode & 0x000F;
    uint16_t nnn = opcode & 0x0FFF;

    pc += 2;
    switch (opcode & 0xF000) {
    case 0x0000:
        if (opcode == 0x00E0) {
            std::memset(display, 0, sizeof(display));
        } else if (opcode == 0x00EE) {
            sp--;
            pc = stack[sp];
        }
        break;
    case 0x1000:
        pc = nnn;
        break;
    case 0x2000:
        stack[sp] = pc;
        sp++;
        pc = nnn;
        break;
    case 0x3000:
        if (kk == reg[x]) {
            pc = pc + 2;
        }
        break;
    case 0x4000:
        if (kk != reg[x]) {
            pc = pc + 2;
        }
        break;
    case 0x5000:
        if (reg[x] == reg[y]) {
            pc = pc + 2;
        }
        break;
    case 0x6000:
        reg[x] = kk;
        break;
    case 0x7000:
        reg[x] += kk;
        break;
    case 0x8000:
        switch (n) {
            case 0: 
                reg[x] = reg[y];
                break;
            case 1: 
                reg[x] |= reg[y];
                break;
            case 2: 
                reg[x] &= reg[y];
                break;
            case 3: 
                reg[x] ^= reg[y];
                break;
            case 4: 
                reg[0xF] = (reg[x]+reg[y]) > 255;
                reg[x] += reg[y];
                break;
            case 5:
                reg[0xF] = reg[x] > reg[y];
                reg[x] = reg[x] - reg[y];
                break;
            case 6:
                reg[0xF] = reg[x] & 0x1;
                reg[x] /= 2;
                break;
            case 7:
                reg[0xF] = reg[y] > reg[x];
                reg[x] = reg[y] - reg[x];
                break;
            case 0xE: 
                reg[0xF] = (reg[x] & 0x80) >> 7;
                reg[x] <<= 1;
                break;
        }    
        break;
    case 0x9000:
        if (reg[x] != reg[y]) {
            pc += 2;
        }
        break;
    case 0xA000:
        idx_reg = nnn;
        break;
    case 0xB000:
        pc = nnn + reg[0];
        break;
    case 0xC000:
        reg[x] = dist(rng) & kk;
        break;
    case 0xD000: {
        uint8_t vx = reg[x] % 64;   // starting x, wrapped to screen width
        uint8_t vy = reg[y] % 32;   // starting y, wrapped to screen height
        reg[0xF] = 0;              

        for (int row = 0; row < n; row++) {
            uint8_t sprite_byte = mem[idx_reg + row];
            for (int col = 0; col < 8; col++) {
                uint8_t sprite_pixel = (sprite_byte >> (7 - col)) & 0x1;
                if (sprite_pixel) {
                    int px = (vx + col) % 64;
                    int py = (vy + row) % 32;
                    int index = py * 64 + px;
                    if (display[index] == 1) {
                        reg[0xF] = 1;  
                    }
                    display[index] ^= 1;
                }
            }
        }
        break;
    }
    case 0xE000:
        switch (kk) {
        case 0x9E:  
            if (keys[reg[x]]) pc += 2;
            break;
        case 0xA1:   
            if (!keys[reg[x]]) pc += 2;
            break;
        }
        break; 
    case 0xF000:
        switch (kk) {
        case 0x07:   
            reg[x] = delay_timer;
            break;

        case 0x0A: { 
            bool pressed = false;
            for (int i = 0; i < 16; i++) {
                if (keys[i]) {
                    reg[x] = i;
                    pressed = true;
                    break;
                }
            }
            if (!pressed) pc -= 2;   // no key yet - re-run this instruction next cycle
            break;
        }

        case 0x15:   
            delay_timer = reg[x];
            break;

        case 0x18:  
            sound_timer = reg[x];
            break;

        case 0x1E:  
            idx_reg += reg[x];
            break;

        case 0x29:   
            idx_reg = 0x50 + (reg[x] * 5);
            break;

        case 0x33: { // store BCD of Vx at I, I+1, I+2
            uint8_t value = reg[x];
            mem[idx_reg + 2] = value % 10;
            value /= 10;
            mem[idx_reg + 1] = value % 10;
            value /= 10;
            mem[idx_reg]     = value % 10;
            break;
        }

        case 0x55:   
            for (int i = 0; i <= x; i++)
                mem[idx_reg + i] = reg[i];
            break;

        case 0x65:   
            for (int i = 0; i <= x; i++)
                reg[i] = mem[idx_reg + i];
            break;
        }
        break;
    default:
        break;
    }
}

void chip8::tick_timers() {
    if (delay_timer > 0) delay_timer--;
    if (sound_timer > 0) sound_timer--;
}

void chip8::set_keys(const bool* pressed_keys) {
    for (int i{}; i < 16; i++) {
        keys[i] = pressed_keys[i];
    }
}