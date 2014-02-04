#include "Tile.h"


Tile::Tile(sf::Sprite s,float h, float w,bool p)
{
	sprite = s;
	height = h;
	width = w;
	passable = p;
}


Tile::~Tile(void)
{
}
