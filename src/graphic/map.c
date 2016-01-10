#include "map.h"

extern void drawImage(SDL_Surface *, int, int);

void map_load(Map *map, char *name) {
    int x, y;
    FILE *fp;

    fp = fopen(name, "rb");

    /* If we can't open the map then exit */
    if (fp == NULL) {
        printf("Failed to open map %s\n", name);
        exit(1);
    }

    /* Read the data from the file into the map */
    for (y=0;y<MAP_MAX_Y;y++) {
        for (x=0;x<MAP_MAX_X;x++) {
            fscanf(fp, "%d", &map->tile[y][x]);
        }
    }

    /* Close the file afterwards */
    fclose(fp);
}


void map_draw(Map *map, SDL_Renderer *renderer) {




}

void drawMap(Map *map) {








    /* Draw the background */
    /*drawImage(backgroundImage, 0, 0);

    for (y=0;y<MAP_MAX_Y;y++) {
        for (x=0;x<MAP_MAX_X;x++) {
            if (map->tile[y][x] != 0) {
                drawImage(brickImage, x * MAP_TILE_SIZE, y * MAP_TILE_SIZE);
            }
        }
    }*/
}


