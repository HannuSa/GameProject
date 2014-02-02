#ifndef Tile_H
#define Tile_H
#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile(sf::Texture t,float h, float w,bool p);
	virtual ~Tile(void);
protected:
	sf::Texture texture;
	float height, width;
	bool passable;
};

#endif