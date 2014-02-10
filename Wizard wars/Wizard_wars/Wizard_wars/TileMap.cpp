#include "TileMap.h"
#include <SFML\Graphics.hpp>

TileMap::TileMap(int h,int w)
{
	height = h;
	width = w;
}

TileMap::~TileMap()
{}

void TileMap::AddTile(Tile t)
{
	tiles.push_back(t);
}