#include "system.h"

extern Game *game;

/**
 * Update the collision logic
 * @param entity The next entity to update
 * @param delta The elapsed time
 */
void system_collision_update(Entity *entity, Level *level) {
	if((entity->component_mask & CMP_POSITION) == CMP_POSITION &&
	   (entity->component_mask & CMP_COLLISION) == CMP_COLLISION) {

		// Get the current position and collision bounds of the entity
		Position *position = &entity->position;
		Collision *collision = &entity->collision;

		// Apply the current position to the collision bounds
		collision->bounds->x = (int) position->x;

		collision_check_deadly_entities(level->entities, entity->collision.bounds);

		// Check the collision
		if (collision_check_tiles(level->tiles, collision->bounds) ||
			collision_check_entities(level->entities, collision->bounds)) {
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

		// Check the collision
		if (collision_check_tiles(level->tiles, collision->bounds) ||
			collision_check_entities(level->entities, collision->bounds)) {

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
	if((entity->component_mask & CMP_POSITION) != 0 &&
	   (entity->component_mask & CMP_CHECK_POINT) != 0 &&
	   (entity->component_mask & CMP_HEALTH) !=0 ) {

		if((level->bounds.y + level->bounds.h) < entity->position.y) {
			entity->health.counter--;
			if (entity->health.counter == 0) {
				game->running = false;
				return;
			}

			entity->position.x = entity->check_point.x;
			entity->position.y = entity->check_point.y;
		}
	}
}

/**
 * Update the input logic
 * @param entity The next entity to update
 * @param delta The elapsed time
 */
void system_input_update(Entity *entity, const Uint8 *key, float delta) {
	if((entity->component_mask & CMP_POSITION) == CMP_POSITION &&
	   (entity->component_mask & CMP_VELOCITY) == CMP_VELOCITY &&
	   (entity->component_mask & CMP_JUMP) == CMP_JUMP) {
		if (entity->jump.active) {
			entity->position.y -= entity->jump.currentForce * delta * 1.2 ;
		}
	}

	if((entity->component_mask & CMP_POSITION) == CMP_POSITION &&
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
}

/**
 * Update the gravitation logic
 * @param entity The next entity to update
 * @param delta The elapsed time
 */
void system_gravitation_update(Entity *entity, float delta) {
	if((entity->component_mask & CMP_POSITION) == CMP_POSITION &&
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
	if((entity->component_mask & CMP_POSITION) == CMP_POSITION &&
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
	if ((entity->component_mask & CMP_COLLISION) != 0 &&
		(entity->component_mask & CMP_JUMP) != 0 &&
		(entity->component_mask & CMP_DEADLY) != 0) {
			if (entity->deadly.isDead) {
				entity->jump.active = true;
				entity->jump.currentForce = entity->jump.initialForce;
				entity->component_mask ^= CMP_COLLISION;
			}
		}

}
