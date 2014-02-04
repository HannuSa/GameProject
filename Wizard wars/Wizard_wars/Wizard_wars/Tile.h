#ifndef Tile_H
#define Tile_H
#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile(sf::Sprite s,float h, float w,bool p);
	virtual ~Tile(void);
protected:
	sf::Sprite sprite;
	float height, width;
	bool passable;
};

#endif