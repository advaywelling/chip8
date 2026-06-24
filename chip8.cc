#include "chip8.h"
#include <fstream>
#include <iostream> 
#include <cstring> 

chip8::chip8() {
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
        pc = opcode & 0x0FFF;
        break;
    case 0x2000:
        stack[sp] = pc;
        sp++;
        pc = opcode & 0x0FFF;
        break;
    case 0x3000:
        break;
    case 0x4000:
        break;
    case 0x5000:
        break;
    case 0x6000:
        break;
    case 0x7000:
        break;
    case 0x8000:
        break;
    case 0x9000:
        break;
    case 0xA000:
        break;
    case 0xB000:
        break;
    case 0xC000:
        break;
    case 0xD000:
        break;
    case 0xE000:
        break; 
    case 0xF000:
        break;
    default:
        break;
    }
}