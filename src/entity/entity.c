#include "entity.h"

/**
 * Create a new entity
 */
Entity* entity_create() {
    return malloc(sizeof(Entity));
}

/**
 * Deletes an existing entity
 * @param entity
 */
void entity_delete(Entity *entity) {
    free(entity);
}

/**
 * Render an existing entity
 * @param renderer
 * @param entity
 */
void entity_render(SDL_Renderer *renderer, Entity *entity) {
    if((entity->component_mask & CMP_POSITION) != 0 && (entity->component_mask & CMP_RENDER) != 0) {
        sprite_render(renderer, sprite_get(renderer, entity->render.name), (int) entity->position.x, (int) entity->position.y);
    }
}
