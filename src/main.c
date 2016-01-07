#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("%s", SDL_GetError());
        return 1;
    } else {
        printf("SDL is working correctly.");
    }

    SDL_Quit();
    return 0;
}
