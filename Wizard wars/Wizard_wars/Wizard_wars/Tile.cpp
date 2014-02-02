#include "Tile.h"


Tile::Tile(sf::Texture t,float h, float w,bool p)
{
	texture = t;
	height = h;
	width = w;
	passable = p;
}


Tile::~Tile(void)
{
}
