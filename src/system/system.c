#include "system.h"

#define SYSTEM_GRAVITY_FACTOR 35

void sys_render_update(Entities *entities, SDL_Renderer *renderer)
{
	//UI/HUD elements defined as render components without position
	//Object sprites defined as render components + position

	unsigned int entity;
	//struct cmp_position *pos;
	//struct cmp_position *render;

	for(entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if((entities->component_mask[entity] & CMP_RENDER) == CMP_RENDER)
		{
			//TODO: use get_sprite here with the graphic database and draw it with SDL_RenderCopy()

			Sprite *sprite = sprite_get(entities->renders[entity].name);

			//fill out position rect if it contains a position component, otherwise use defaults.
			int w, h;
			SDL_Rect pos_rect;
			pos_rect.x = 0;
			pos_rect.y = 0;
			if((entities->component_mask[entity] & CMP_POSITION) == CMP_POSITION)
			{
				pos_rect.x = entities->positions[entity].x;
				pos_rect.y = entities->positions[entity].y;
			}
			SDL_QueryTexture(sprite->texture, NULL, NULL, &w, &h);
			pos_rect.w = w;
			pos_rect.h = h;
			SDL_RenderCopy(renderer, sprite->texture, NULL, &pos_rect);
		}
	}
}

void sys_collision_update(Level *level, Entities *entities) {
	for(int entity = 0; entity < ENTITY_COUNT; ++entity) {
		if((entities->component_mask[entity] & CMP_POSITION) == CMP_POSITION &&
		   (entities->component_mask[entity] & CMP_COLLISION) == CMP_COLLISION) {

			// Get the current position and collision bounds of the entity
			Position *position = &entities->positions[entity];
			Collision *collision = &entities->collisions[entity];

			// Apply the current position to the collision bounds
			collision->bounds->x = (int) position->x;

			// Check the collision
			if (collision_check_tiles(level->tiles, level->tileFree, collision->bounds) ||
				collision_check_entities(entities, collision->bounds)) {
				position->x = position->oldX;
				collision->bounds->x = (int) position->oldX;

				if((entities->component_mask[entity] & CMP_STRAIGHT_MOVEMENT) == CMP_STRAIGHT_MOVEMENT) {
					if (strcmp(entities->straightMovements[entity].direction, "left") == 0) {
						entities->straightMovements[entity].direction = "right";
					} else {
						entities->straightMovements[entity].direction = "left";
					}
				}
			}

			// Set the old position for the next time
			position->oldX = position->x;

			// --------------------------------------

			// Apply the current position to the collision bounds
			collision->bounds->y = (int) position->y;

			// Check the collision
			if (collision_check_tiles(level->tiles, level->tileFree, collision->bounds) ||
				collision_check_entities(entities, collision->bounds)) {

				if((entities->component_mask[entity] & CMP_JUMP) == CMP_JUMP && entities->jumps[entity].active == true) {
					if (position->y > position->oldY) {
						entities->jumps[entity].active = false;
					}

					entities->jumps[entity].currentForce = 0;
				}

				position->y = position->oldY;
				collision->bounds->y = (int) position->oldY;
			}

			// Set the old position for the next time
			position->oldY = position->y;
		}
	}
}

void sys_input_update(Level *level, Entities *entities, const Uint8 *key, float delta) {
	for(int entity = 0; entity < ENTITY_COUNT; ++entity) {
		if((entities->component_mask[entity] & CMP_POSITION) == CMP_POSITION &&
		   (entities->component_mask[entity] & CMP_VELOCITY) == CMP_VELOCITY &&
		   (entities->component_mask[entity] & CMP_COLLISION) == CMP_COLLISION) {

			if ((entities->component_mask[entity] & CMP_JUMP) == CMP_JUMP) {
				if (key[SDL_SCANCODE_UP] && entities->jumps[entity].active == false) {
					entities->jumps[entity].active = true;
					entities->jumps[entity].currentForce = entities->jumps[entity].initialForce;
				}

				if (entities->jumps[entity].active) {
					entities->positions[entity].y -= entities->jumps[entity].currentForce * delta * 1.2 ;
				}
			}

			if ((entities->component_mask[entity] & CMP_INPUT_PLAYER) == CMP_INPUT_PLAYER ) {
				if (key[SDL_SCANCODE_LEFT]) {
					entities->positions[entity].x -= entities->velocities[entity].x * delta;
				}
				if (key[SDL_SCANCODE_RIGHT]) {
					entities->positions[entity].x += entities->velocities[entity].x * delta;
				}
			}
		}
	}
}

void sys_gravitation_update(Level *level, Entities *entities, float delta) {
	for(unsigned int entity = 0; entity < ENTITY_COUNT; ++entity) {
		if((entities->component_mask[entity] & CMP_POSITION) == CMP_POSITION &&
		   (entities->component_mask[entity] & CMP_VELOCITY) == CMP_VELOCITY &&
		   (entities->component_mask[entity] & CMP_COLLISION) == CMP_COLLISION &&
		   (entities->component_mask[entity] & CMP_GRAVITATION) == CMP_GRAVITATION ) {

			entities->positions[entity].y += 0.5 * SYSTEM_GRAVITY_FACTOR * 9.81 * delta;

			if ((entities->component_mask[entity] & CMP_JUMP) == CMP_JUMP) {
				if (entities->jumps[entity].active) {
					entities->jumps[entity].currentForce -= 0.5 * SYSTEM_GRAVITY_FACTOR * 9.81 * delta * 1.5;
				}
			}
		}
	}
}

void sys_straight_movement_update(Level *level, Entities *entities, float delta) {
	for(unsigned int entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if((entities->component_mask[entity] & CMP_POSITION) == CMP_POSITION &&
		   (entities->component_mask[entity] & CMP_VELOCITY) == CMP_VELOCITY &&
		   (entities->component_mask[entity] & CMP_STRAIGHT_MOVEMENT) == CMP_STRAIGHT_MOVEMENT) {

			if (strcmp(entities->straightMovements[entity].direction, "left") == 0) {
				entities->positions[entity].x -= entities->velocities[entity].x * delta;
			} else {
				entities->positions[entity].x += entities->velocities[entity].x * delta;
			}
		}
	}
}
