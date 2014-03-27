#ifndef TileMap_H
#define TileMap_H

#include "Tile.h"

#define TILEMAP_WIDTH 100
#define TILEMAP_HEIGHT 100

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class TileMap
{
public:
	TileMap();
	~TileMap(void);

	TileType tiles[TILEMAP_WIDTH][TILEMAP_HEIGHT];
};

#endif