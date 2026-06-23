#pragma once
#include <cstdint>
#include <string>

class chip8 {
    public:
        chip8();
        bool load_rom(const std::string& filename);
        void cycle();
        const uint8_t* get_display() const;
        void set_keys(const bool* pressed_keys);

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
};