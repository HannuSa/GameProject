#ifndef Tile_H
#define Tile_H
#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile(sf::Sprite s,bool p);
	virtual ~Tile(void);
protected:
	sf::Sprite sprite;
	bool passable;
};

#endif