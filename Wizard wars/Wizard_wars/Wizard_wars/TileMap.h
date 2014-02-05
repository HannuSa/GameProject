#ifndef TileMap_H
#define TileMap_H

#include "Tile.h"

class TileMap
{
public:
	TileMap(int h, int w);
	~TileMap(void);
	void AddTile(Tile t);
	void Draw();
private:
	int height,width;
	std::vector<Tile> tiles;
};

#endif