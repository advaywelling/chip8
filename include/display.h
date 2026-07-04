#pragma once
#include <SDL.h>
#include <cstdint>

class Display {
    public:
        Display(const char* text, int width, int height);
        ~Display();

        void update(const uint8_t* display);
        bool input(bool* keys);

    private: 
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;
};

