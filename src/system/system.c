#include "system.h"

void sys_render_update(Entities *entities, Sprites *sprites, SDL_Renderer *renderer)
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
			int sprite = sprite_get(sprites, renderer, entities->renders[entity].name);

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
			SDL_QueryTexture(sprites->textures[sprite], NULL, NULL, &w, &h);
			pos_rect.w = w;
			pos_rect.h = h;
			SDL_RenderCopy(renderer, sprites->textures[sprite], NULL, &pos_rect);
		}
	}

}

void sys_input_update(Entities *entities, const Uint8 *key)
{
	int entity;
	for(entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if((entities->component_mask[entity] & CMP_INPUT_PLAYER) == CMP_INPUT_PLAYER)
		{
			if(key[SDL_SCANCODE_UP])
				entities->positions[entity].y-=2.0f;
			if(key[SDL_SCANCODE_DOWN])
				entities->positions[entity].y+=2.0f;
			if(key[SDL_SCANCODE_LEFT])
				entities->positions[entity].x-=2.0f;
			if(key[SDL_SCANCODE_RIGHT])
				entities->positions[entity].x+=2.0f;
		}
	}
}
