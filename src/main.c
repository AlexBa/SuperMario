#include <stdio.h>
#include <SDL2/SDL.h>
#include "entity.h"

const Uint8 *key;

unsigned int create_player(Entities *entities, float x, float y)
{
    unsigned int entity = entity_create(entities);
    entities->component_mask[entity] = CMP_POSITION | CMP_COLLISION;

    entities->positions[entity].x = x;
    entities->positions[entity].y = y;
    entities->collisions[entity].x = x;
    entities->collisions[entity].y = y;

    return entity;
}

int main(int argc, char** argv) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("%s", SDL_GetError());
        return 1;
    } else {
        printf("SDL is working correctly.\n\n");
    }

    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_RESIZABLE, &window, &renderer);
    if(window==NULL) {
        printf("Error: Could not create window. %s", SDL_GetError());
    }
    if(renderer==NULL) {
        printf("Error: Could not create renderer. %s", SDL_GetError());
    }

    SDL_RenderSetLogicalSize(renderer, 800, 600);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    int done = 0;
    while(!done){
        key = SDL_GetKeyboardState(NULL);
        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
                case SDL_QUIT:
                    done = 1;
                    break;
                case SDL_KEYDOWN:
                    if(ev.key.keysym.sym == SDLK_ESCAPE)
                        done = 1;
                    if(ev.key.keysym.sym == SDLK_p)
                        break;
                case SDL_KEYUP:
                    break;
                default:
                    break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    // Example code
    Entities entities;
    unsigned int player_id = create_player(&entities, 10, 10);
    printf("PosX: %f\n", entities.positions[player_id].x);
    printf("PosY: %f\n", entities.positions[player_id].y);
    entity_destroy(&entities, player_id);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
