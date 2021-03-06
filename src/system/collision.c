#include "collision.h"

/**
 * This function tests if the two boxes are colliding.
 * @param rect1 The first collision box
 * @param rect2 The second collision box
 * @return Indicates if a collision has occurred
 */
bool collision_check(SDL_Rect *rect1, SDL_Rect *rect2) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = rect1->x;
    rightA =rect1->x + rect1->w;
    topA = rect1->y;
    bottomA = rect1->y + rect1->h;

    //Calculate the sides of rect B
    leftB = rect2->x;
    rightB = rect2->x + rect2->w;
    topB = rect2->y;
    bottomB = rect2->y + rect2->h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB ) {
        return false;
    }

    if( topA >= bottomB ) {
        return false;
    }

    if( rightA <= leftB ) {
        return false;
    }

    if( leftA >= rightB ) {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

/**
 * Check if the level is colliding with the rect
 * @param level The collision for the level
 * @param rect The rect to check
 */
bool collision_check_level(Level *level, SDL_Rect *rect) {
    return collision_check(&level->bounds, rect);
}

/**
 * Check if the rect is colliding with any entity
 * @param tiles The array of entities to check
 * @param tileFree Indicates if a tile exists at the given position
 * @param rect The rect to check
 */
bool collision_check_entities(Entity *entities[], SDL_Rect *rect) {
    for(int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
                if (entities[i] != NULL) {
                    Entity *entity = entities[i];

                    if ((entity->component_mask & CMP_COLLISION) != 0) {
                        Collision *collision = &entity->collision;

                        if (collision->bounds != rect &&
                            collision_check(collision->bounds, rect)) {
                            return true;
                        }
                    }
        }
    }

    return false;
}

bool collision_check_deadly_entities(Entity *entities[], SDL_Rect *rect) {
    for(int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        if (entities[i] != NULL) {
            Entity *entity = entities[i];
            if ((entity->component_mask & CMP_COLLISION) != 0 &&
                (entity->component_mask & CMP_DEADLY) != 0) {
                Collision *collision = &entity->collision;
                Deadly *deadly = &entity->deadly;

                if (collision->bounds != rect &&
                    collision_check(collision->bounds, rect)) {
                    deadly->isDead = true;
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * Check if the rect is colliding with any tile
 * @param tiles The array of tiles to check
 * @param tileFree Indicates if a tile exists at the given position
 * @param rect The rect to check
 */
bool collision_check_tiles(Tile *tiles[], SDL_Rect *rect) {
    for(int i = 0; i < LEVEL_TILE_COUNT; i++) {
        if (tiles[i] != NULL && collision_check(tiles[i]->bounds, rect)) {
            return true;
        }
    }

    return false;
}

bool collision_check_player_kills_enemy(Entity *entities[], Entity *player) {
    for(int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        Entity *enemy = entities[i];

        if (enemy != NULL && enemy != player &&
           (enemy->component_mask & CMP_ENEMY) != 0 &&
           (enemy->component_mask & CMP_COLLISION) != 0) {
            if (collision_check(player->collision.bounds, enemy->collision.bounds)) {
                if (player->position.oldY <= player->position.y) {
                    enemy->enemy.alive = false;
                }
                return true;
            }
        }
    }

    return false;
}

bool collision_check_enemy_kills_player(Entity *entities[], Entity *enemy) {
    for(int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        Entity *player = entities[i];

        if (player != NULL && player != enemy &&
            (player->component_mask & CMP_PLAYER) != 0 &&
            (player->component_mask & CMP_HEALTH) != 0 &&
            (player->component_mask & CMP_COLLISION) != 0) {
            if (collision_check(enemy->collision.bounds, player->collision.bounds)) {
                if (enemy->position.oldX != enemy->position.x) {
                    player->player.alive = false;
                }
                return true;
            }
        }
    }

    return false;
}

bool collision_check_item_touches_player(Entity *entities[], Entity *item) {
    for(int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        Entity *player = entities[i];

        if (player != NULL && player != item &&
            (player->component_mask & CMP_PLAYER) != 0 &&
            (player->component_mask & CMP_COLLISION) != 0) {
            if (collision_check(item->collision.bounds, player->collision.bounds)) {
                player->player.touchedItem = item->item.type;

                return true;
            }
        }
    }

    return false;
}

bool collision_check_bullet_kills_player(Entity *entities[], Entity *bullet) {
    for(int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        Entity *player = entities[i];

        if (player != NULL && player != bullet &&
            (player->component_mask & CMP_PLAYER) != 0 &&
            (player->component_mask & CMP_COLLISION) != 0) {
            if (collision_check(bullet->collision.bounds, player->collision.bounds)) {
                player->player.alive = false;
                return true;
            }
        }
    }

    return false;
}

bool collision_check_bullet_kills_enemy(Entity *entities[], Entity *bullet) {
    for(int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        Entity *enemy = entities[i];

        if (enemy != NULL && enemy != bullet &&
            (enemy->component_mask & CMP_ENEMY) != 0 &&
            (enemy->component_mask & CMP_COLLISION) != 0) {
            if (collision_check(bullet->collision.bounds, enemy->collision.bounds)) {
                enemy->enemy.alive = false;
                return true;
            }
        }
    }

    return false;
}