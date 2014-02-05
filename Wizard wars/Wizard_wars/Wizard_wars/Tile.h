#ifndef Tile_H
#define Tile_H
#include <SFML\Graphics.hpp>

class Tile
{
	friend class TileMap;
public:
	Tile(sf::Sprite s,bool p,sf::Vector2<int> pos);
	virtual ~Tile(void);
protected:
	sf::Sprite sprite;
	sf::Vector2<int> position;
	bool passable;
};

#endif