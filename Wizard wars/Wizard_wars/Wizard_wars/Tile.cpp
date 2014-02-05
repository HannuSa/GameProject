#include "Tile.h"


Tile::Tile(sf::Sprite s,bool p,sf::Vector2<int> pos)
{
	sprite = s;
	position = pos;
	passable = p;
}


Tile::~Tile(void)
{
}
