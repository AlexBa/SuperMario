#include "game.h"

/**
 * Create a new game
 * @return The newly created game or NULL on any error
 */
Game* game_create() {
    Game *game = malloc(sizeof(Game));
    game->window = NULL;
    game->renderer = NULL;
    game->pause = false;
    game->running = false;

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_INPUT_GRABBED, &game->window, &game->renderer);
    if (game->window == NULL || game->renderer == NULL) {
        printf("ERROR: Failed to create the game: %s", SDL_GetError());
        return NULL;
    }

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_ShowCursor(SDL_DISABLE);

    return game;
}

/**
 * Delete an existing game
 */
void game_delete(Game *game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game);
}

/**
 * Run the game
 */
void game_run(Game *game) {
    //TODO: Example code. Remove it later
    game->level = level_create(game->renderer, "back.bmp");

    /*
    // Create the player
    Entity *player = player_create(64.0f, 240.0f);
    level_add_entity(game->level, player);

    // Create the enemy
    Entity *enemy = enemy_create(300.0f, 60.0f);
    level_add_entity(game->level, enemy);

    // Create the enemy
    Entity *mushroom = mushroom_create(400.0f, 60.0f);
    level_add_entity(game->level, mushroom);
    */
    game->last_ticks = SDL_GetTicks();
    game_continue(game);

    game->running = true;
    while(game->running){
        game->key = SDL_GetKeyboardState(NULL);
        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
                case SDL_QUIT:
                    game->running = false;
                    break;
                case SDL_KEYDOWN:
                    if(ev.key.keysym.sym == SDLK_ESCAPE)
                        game->running = false;
                    if(ev.key.keysym.sym == SDLK_p)
                        break;
                case SDL_KEYUP:
                    break;
                default:
                    break;
            }
        }

        if (game->pause == false) {
            // Calculate the delta time
            game->current_ticks = SDL_GetTicks();
            float delta = (game->current_ticks - game->last_ticks) / 1000.0f;
            game->last_ticks = game->current_ticks;

            game_update(game, delta);
            game_render(game, delta);
        }
    }

    level_delete(game->level);
}

/**
 * Continue the game
 */
void game_continue(Game *game) {
    game->pause = false;
}

/**
 * Pause the game
 */
void game_pause(Game *game) {
    game->pause = true;
}

/**
 * Update the game logic
 * @param game The game to update
 * @param delta The elapsed time since the last run
 */
void game_update(Game *game, float delta) {
    level_scroll(game->level);

    for(int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        if (game->level->entities[i] != NULL) {
            system_input_update(game->level->entities[i], game->key, delta);
            system_straight_movement_update(game->level->entities[i], delta);
            system_gravitation_update(game->level->entities[i], delta);
            system_health_update(game->level->entities[i], game->level);
            system_deadly_update(game->level->entities[i], game->level);
            system_bullet_update(game->level->entities[i], game->level);
            system_collision_update(game->level->entities[i], game->level);
            system_shooting_update(game->level->entities[i], game->level, delta);
        }
    }
}

/**
 * Update the game graphics
 * @param game The game to render
 * @param delta The elapsed time since the last run
 */

void game_render(Game *game, float delta) {
    SDL_RenderClear(game->renderer);
    level_render(game->renderer, game->level);
    SDL_RenderPresent(game->renderer);
}
