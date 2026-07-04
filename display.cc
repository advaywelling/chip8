#include <SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Chip-8",                       
        SDL_WINDOWPOS_CENTERED,         
        SDL_WINDOWPOS_CENTERED,       
        640, 320,          
        SDL_WINDOW_SHOWN               
    );

    SDL_Delay(2000);        

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}