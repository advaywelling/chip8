#pragma once
#include <cstdint>
#include <string>
#include <random>

class chip8 {
    public:
        chip8();
        bool load_rom(const std::string& filename);
        void cycle();
        const uint8_t* get_display() const;
        void set_keys(const bool* pressed_keys);
        uint16_t get_pc() const { return pc; }
    private:
        uint8_t reg[16]{};
        uint8_t mem[4096]{};
        uint16_t idx_reg{};
        uint16_t pc{};
        uint16_t stack[16]{};
        uint8_t sp{};
        uint8_t delay_timer{};
        uint8_t sound_timer{};
        uint8_t display[64 * 32]{};   
        bool keys[16]{}; 
        std::mt19937 rng;
        std::uniform_int_distribution<int> dist{0,255};
};