#include <stdio.h>
#include <SDL2/SDL.h>
#include "entity.h"

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
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("%s", SDL_GetError());
        return 1;
    } else {
        printf("SDL is working correctly.\n\n");
    }

    Entities entities;

    // Example code
    unsigned int player_id = create_player(&entities, 10, 10);
    printf("PosX: %f\n", entities.positions[0].x);
    printf("PosY: %f\n", entities.positions[0].y);
    entity_destroy(&entities, player_id);

    SDL_Quit();
    return 0;
}
