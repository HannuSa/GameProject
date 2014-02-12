#include "TileMap.h"
#include <SFML\Graphics.hpp>

TileMap::TileMap()
{
	for(int x = 0; x < TILEMAP_WIDTH; ++x)
	{
		for(int y = 0; y < TILEMAP_HEIGHT; ++y)
		{
			tiles[x][y] =(TileType)1;
		}
	}
}

TileMap::~TileMap()
{}