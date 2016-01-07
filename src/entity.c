#include "entity.h"

unsigned int entity_create(Entities *entities)
{
    unsigned int entity;
    for(entity = 0; entity < ENTITY_COUNT; ++entity)
    {
        if(entities->component_mask[entity] == CMP_NONE)
        {
            return entity;
        }
    }

    printf("Error: no more entities.\n");
    return ENTITY_COUNT;
}

void entity_destroy(Entities *entities, unsigned int entity)
{
    entities->component_mask[entity] = CMP_NONE;
}
