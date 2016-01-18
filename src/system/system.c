#include "system.h"

#define SYSTEM_GRAVITY_FACTOR 25

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

void sys_input_update(Level *level, Entities *entities, const Uint8 *key, float delta) {
	for(int entity = 0; entity < ENTITY_COUNT; ++entity) {
		if((entities->component_mask[entity] & CMP_POSITION) == CMP_POSITION &&
		   (entities->component_mask[entity] & CMP_VELOCITY) == CMP_VELOCITY &&
		   (entities->component_mask[entity] & CMP_COLLISION) == CMP_COLLISION &&
		   (entities->component_mask[entity] & CMP_INPUT_PLAYER) == CMP_INPUT_PLAYER ) {


			if (key[SDL_SCANCODE_UP]) {
				entities->positions[entity].y -= entities->velocities[entity].y * delta;
				entities->collisions[entity].bounds->y = (int) entities->positions[entity].y;
			}
			if (key[SDL_SCANCODE_DOWN]) {
				entities->positions[entity].y += entities->velocities[entity].y * delta;
				entities->collisions[entity].bounds->y = (int) entities->positions[entity].y;
			}
			if (key[SDL_SCANCODE_LEFT]) {
				entities->positions[entity].x -= entities->velocities[entity].x * delta;
				entities->collisions[entity].bounds->x = (int) entities->positions[entity].x;
			}
			if (key[SDL_SCANCODE_RIGHT]) {
				entities->positions[entity].x += entities->velocities[entity].x * delta;
				entities->collisions[entity].bounds->x = (int) entities->positions[entity].x;
			}

			bool willCollide = false;
			for(int i = 0; i < LEVEL_TILE_COUNT; i++) {
				if (level->tileFree[i] == 0) {
					Position *p = &entities->positions[entity];
					Collision *c = &entities->collisions[entity];
					Tile *t = level->tiles[i];

					SDL_Rect futureBounds;
					futureBounds.x = (int)p->x;
					futureBounds.y = (int)p->y;
					futureBounds.w = c->bounds->w;
					futureBounds.h = c->bounds->h;

					willCollide = collision_check(&futureBounds, t->bounds);
					if (willCollide) {
						break;
					}
				}
			}

            if (willCollide == true) {
				if (key[SDL_SCANCODE_UP]) {
					entities->positions[entity].y += entities->velocities[entity].y * delta;
					entities->collisions[entity].bounds->y = (int) entities->positions[entity].y;
				}
				if (key[SDL_SCANCODE_DOWN]) {
					entities->positions[entity].y -= entities->velocities[entity].y * delta;
					entities->collisions[entity].bounds->y = (int) entities->positions[entity].y;
				}
				if (key[SDL_SCANCODE_LEFT]) {
					entities->positions[entity].x += entities->velocities[entity].x * delta;
					entities->collisions[entity].bounds->x = (int) entities->positions[entity].x;
				}
				if (key[SDL_SCANCODE_RIGHT]) {
					entities->positions[entity].x -= entities->velocities[entity].x * delta;
					entities->collisions[entity].bounds->x = (int) entities->positions[entity].x;
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

			bool willCollide = false;
			for(int i = 0; i < LEVEL_TILE_COUNT; i++) {
				if (level->tileFree[i] == 0) {
					Position *p = &entities->positions[entity];
					Collision *c = &entities->collisions[entity];
					Tile *t = level->tiles[i];

					SDL_Rect futureBounds;
					futureBounds.x = (int)p->x;
					futureBounds.y = (int)p->y;
					futureBounds.w = c->bounds->w;
					futureBounds.h = c->bounds->h;

					willCollide = collision_check(&futureBounds, t->bounds);
					if (willCollide) {
						break;
					}
				}
			}

			if (willCollide) {
				entities->positions[entity].y -= 0.5 * SYSTEM_GRAVITY_FACTOR * 9.81 * delta;
			}
		}
	}
}

void sys_straight_movement_update(Level *level, Entities *entities, float delta) {
	for(unsigned int entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if((entities->component_mask[entity] & CMP_POSITION) == CMP_POSITION &&
		   (entities->component_mask[entity] & CMP_VELOCITY) == CMP_VELOCITY &&
		   (entities->component_mask[entity] & CMP_COLLISION) == CMP_COLLISION &&
		   (entities->component_mask[entity] & CMP_STRAIGHT_MOVEMENT) == CMP_STRAIGHT_MOVEMENT &&
		   (entities->component_mask[entity] & CMP_GRAVITATION) == CMP_GRAVITATION ) {



			if (strcmp(entities->straightMovements[entity].direction, "left") == 0) {
				entities->positions[entity].x -= entities->velocities[entity].x * delta;
			} else {
				entities->positions[entity].x += entities->velocities[entity].x * delta;
			}

			bool willCollide = false;
			for(int i = 0; i < LEVEL_TILE_COUNT; i++) {
				if (level->tileFree[i] == 0) {
					Position *p = &entities->positions[entity];
					Collision *c = &entities->collisions[entity];
					Tile *t = level->tiles[i];

					SDL_Rect futureBounds;
					futureBounds.x = (int)p->x;
					futureBounds.y = (int)p->y;
					futureBounds.w = c->bounds->w;
					futureBounds.h = c->bounds->h;

					willCollide = collision_check(&futureBounds, t->bounds);
					if (willCollide) {
						break;
					}
				}
			}

			if (willCollide) {
				if (strcmp(entities->straightMovements[entity].direction, "left") == 0) {
					entities->positions[entity].x += entities->velocities[entity].x * delta;
					entities->straightMovements[entity].direction = "right";
				} else {
					entities->positions[entity].x -= entities->velocities[entity].x * delta;
					entities->straightMovements[entity].direction = "left";
				}
			}
		}
	}
}
