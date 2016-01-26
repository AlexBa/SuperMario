#include "system.h"

extern Game *game;

/**
 * Update the collision logic
 * @param entity The next entity to update
 * @param delta The elapsed time
 */
void system_collision_update(Entity *entity, Level *level) {
	if(entity != NULL &&
	   (entity->component_mask & CMP_POSITION) == CMP_POSITION &&
	   (entity->component_mask & CMP_COLLISION) == CMP_COLLISION) {

		// Get the current position and collision bounds of the entity
		Position *position = &entity->position;
		Collision *collision = &entity->collision;

		// Apply the current position to the collision bounds
		collision->bounds->x = (int) position->x;

		if ((entity->component_mask & CMP_ENEMY) != 0) {
			collision_check_enemy_kills_player(level->entities, entity);
		}

		if ((entity->component_mask & CMP_ITEM) != 0 &&
			collision_check_item_touches_player(level->entities, entity)) {
			level_remove_entity(level, entity);
			return;
		}

		// Check the collision
		if (collision_check_tiles(level->tiles, collision->bounds) ||
			collision_check_entities(level->entities, collision->bounds)) {
			if((entity->component_mask & CMP_BULLET) != 0) {
				collision_check_bullet_kills_enemy(level->entities, entity);
				level_remove_entity(level, entity);
				return;
			}

			position->x = position->oldX;
			collision->bounds->x = (int) position->oldX;

			if((entity->component_mask & CMP_STRAIGHT_MOVEMENT) == CMP_STRAIGHT_MOVEMENT) {
				if (strcmp(entity->straightMovement.direction, "left") == 0) {
					entity->straightMovement.direction = "right";
				} else {
					entity->straightMovement.direction = "left";
				}
			}
		}

		// Set the old position for the next time
		position->oldX = position->x;

		// --------------------------------------

		// Apply the current position to the collision bounds
		collision->bounds->y = (int) position->y;

		if ((entity->component_mask & CMP_PLAYER) != 0) {
			collision_check_player_kills_enemy(level->entities, entity);
		}

		if ((entity->component_mask & CMP_ITEM) != 0 &&
			collision_check_item_touches_player(level->entities, entity)) {
			level_remove_entity(level, entity);
			return;
		}

		// Check the collision
		if (collision_check_tiles(level->tiles, collision->bounds)) {

			if((entity->component_mask & CMP_JUMP) == CMP_JUMP && entity->jump.active == true) {
				if (position->y > position->oldY) {
					entity->jump.active = false;
				}

				entity->jump.currentForce = 0;
			}

			position->y = position->oldY;
			collision->bounds->y = (int) position->oldY;
		}

		// Set the old position for the next time
		position->oldY = position->y;
	}
}

/**
 * Update the health logic
 * @param entity
 * @param level
 */
void system_health_update(Entity *entity, Level *level) {
	if(entity != NULL &&
	   (entity->component_mask & CMP_POSITION) != 0 &&
	   (entity->component_mask & CMP_CHECK_POINT) != 0 &&
	   (entity->component_mask & CMP_JUMP) != 0 &&
	   (entity->component_mask & CMP_HEALTH) !=0 ) {

		// The player has to jump on death
		if (entity->player.alive == false && entity->jump.active == false) {
			entity->jump.active = true;
			entity->jump.currentForce = entity->jump.initialForce;
			entity->component_mask ^= CMP_COLLISION;
			return;
		}

		// Check if the player has fallen off the level
		if((level->bounds.y + level->bounds.h) < entity->position.y) {
			// Quit the game if the player has no live anymore
			if (entity->health.counter <= 1) {
				game->running = false;
				return;
			}

			// Reset the player with one live less
			entity->health.counter--;
			entity->component_mask |= CMP_COLLISION;
			entity->position.x = entity->check_point.x;
			entity->position.y = entity->check_point.y;
			entity->player.alive = true;
			entity->jump.active = false;
		}
	}
}

/**
 * Update the input logic
 * @param entity The next entity to update
 * @param delta The elapsed time
 */
void system_input_update(Entity *entity, const Uint8 *key, float delta) {
	if(entity != NULL &&
	   (entity->component_mask & CMP_POSITION) == CMP_POSITION &&
	   (entity->component_mask & CMP_VELOCITY) == CMP_VELOCITY &&
	   (entity->component_mask & CMP_JUMP) == CMP_JUMP) {
		if (entity->jump.active) {
			entity->position.y -= entity->jump.currentForce * delta * 1.2 ;
		}
	}



	if(entity != NULL &&
	   (entity->component_mask & CMP_POSITION) == CMP_POSITION &&
	   (entity->component_mask & CMP_VELOCITY) == CMP_VELOCITY &&
	   (entity->component_mask & CMP_COLLISION) == CMP_COLLISION) {

		if ((entity->component_mask & CMP_JUMP) == CMP_JUMP) {
			if (key[SDL_SCANCODE_UP] && entity->jump.active == false) {
				entity->jump.active = true;
				entity->jump.currentForce = entity->jump.initialForce;
			}
		}

		if ((entity->component_mask & CMP_INPUT_PLAYER) == CMP_INPUT_PLAYER ) {
			if (key[SDL_SCANCODE_LEFT]) {
				entity->position.x -= entity->velocity.x * delta;
			}
			if (key[SDL_SCANCODE_RIGHT]) {
				entity->position.x += entity->velocity.x * delta;
			}
		}
	}


	if(entity != NULL &&
	   (entity->component_mask & CMP_POSITION) != 0 &&
	   (entity->component_mask & CMP_VELOCITY) != 0 &&
	   (entity->component_mask & CMP_COLLISION) != 0 &&
	   (entity->component_mask & CMP_PLAYER) != 0 &&
	   (entity->component_mask & CMP_SHOOTING) != 0) {
		if (key[SDL_SCANCODE_S]) {
			entity->shooting.ready = true;
		}
	}
}

/**
 * Update the gravitation logic
 * @param entity The next entity to update
 * @param delta The elapsed time
 */
void system_gravitation_update(Entity *entity, float delta) {
	if(entity != NULL &&
	   (entity->component_mask & CMP_POSITION) == CMP_POSITION &&
	   (entity->component_mask & CMP_VELOCITY) == CMP_VELOCITY &&
	   (entity->component_mask & CMP_GRAVITATION) == CMP_GRAVITATION ) {

		entity->position.y += 0.5 * SYSTEM_GRAVITY_FACTOR * 9.81 * delta;

		if ((entity->component_mask & CMP_JUMP) == CMP_JUMP) {
			if (entity->jump.active) {
				entity->jump.currentForce -= 0.5 * SYSTEM_GRAVITY_FACTOR * 9.81 * delta * 1.5;
			}
		}
	}
}

/**
 * Update the straight movement logic
 * @param entity The next entity to update
 * @param delta The elapsed time
 */
void system_straight_movement_update(Entity *entity,  float delta) {
	if(entity != NULL &&
	   (entity->component_mask & CMP_POSITION) == CMP_POSITION &&
	   (entity->component_mask & CMP_VELOCITY) == CMP_VELOCITY &&
	   (entity->component_mask & CMP_STRAIGHT_MOVEMENT) == CMP_STRAIGHT_MOVEMENT) {

		if (strcmp(entity->straightMovement.direction, "left") == 0) {
			entity->position.x -= entity->velocity.x * delta;
		} else {
			entity->position.x += entity->velocity.x * delta;
		}
	}
}

void system_deadly_update(Entity *entity, Level *level) {
	if (entity != NULL &&
		(entity->component_mask & CMP_ENEMY) != 0) {
		if (!entity->enemy.alive) {
			level_remove_entity(level, entity);
			return;
		}
	}
}

/**
 * Update the shooting logic
 * @param entity The next entity to update
 * @param level The related level of the entity
 * @param delta The elapsed time
 */
void system_shooting_update(Entity *entity, Level *level, float delta) {
	if (entity != NULL &&
		(entity->component_mask & CMP_POSITION) != 0 &&
		(entity->component_mask & CMP_SHOOTING) != 0) {

		// Count the elapsed time for the next shoot
		entity->shooting.elapsed += delta;
		if (entity->shooting.elapsed >= entity->shooting.rate) {
			if ((entity->component_mask & CMP_ENEMY) != 0) {
				entity->shooting.ready = true;
			}

			if (entity->shooting.ready == true) {
				entity->shooting.ready = false;

				if ((entity->component_mask & CMP_PLAYER) != 0) {
					entity->shooting.elapsed = 0;
				} else {
					entity->shooting.elapsed -= entity->shooting.rate;
				}

				if (strcmp(entity->shooting.bulletType, "fireball") == 0) {
					Entity *fireball = fireball_create(entity->position.x - entity->shooting.bulletSize,
													   entity->position.y, "left");
					level_add_entity(level, fireball);
				}
			}
		}
	}
}

/**
 * Update the bullet logic
 * @param entity The next entity to update
 * @param level The related level of the entity
 */
void system_bullet_update(Entity *entity, Level *level) {
	if (entity != NULL &&
		(entity->component_mask & CMP_ENEMY) != 0 && entity->enemy.alive == false) {
		level_remove_entity(level, entity);
	}

	if (entity != NULL &&
		(entity->component_mask & CMP_COLLISION) != 0 &&
		(entity->component_mask & CMP_BULLET) != 0) {

		if (collision_check_entities(level->entities, entity->collision.bounds) ||
			collision_check_tiles(level->tiles, entity->collision.bounds) ||
			!collision_check_level(level, entity->collision.bounds)) {
			level_remove_entity(level, entity);
		}
	}
}

void system_item_update(Entity *entity, Level *level, float delta) {
	if (entity != NULL &&
		(entity->component_mask & CMP_HEALTH) != 0 &&
		(entity->component_mask & CMP_PLAYER) != 0) {

		// Check if the player collides with an item
		if (entity->player.touchedItem != NULL) {
			if (strcmp(entity->player.touchedItem, "mushroom") == 0) {
				entity->health.counter++;
				printf("Touched mushroom. Life: %d", entity->health.counter);
			} else if (strcmp(entity->player.touchedItem, "fireflower") == 0) {
				entity->component_mask |= CMP_SHOOTING;
				entity->shooting.ready = false;
				entity->shooting.bulletType = "fireball";
				entity->shooting.bulletSize = 5;
				entity->shooting.direction = "right";
				entity->shooting.rate = 0.5f;
				entity->shooting.elapsed = 0;
				entity->shooting.velocityX = -100;
				entity->shooting.velocityY = 0;
				printf("Touched fire flower.");
			}

			entity->player.touchedItem = NULL;
		}
	}

	if (entity != NULL &&
		(entity->component_mask & CMP_ITEM) != 0) {

		if (collision_check_item_touches_player(level->entities, entity)) {
			level_remove_entity(level, entity);
			return;
		}
	}
}
