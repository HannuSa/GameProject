#ifndef TileMap_H
#define TileMap_H

#include "Tile.h"

class TileMap
{
public:
	TileMap(int h, int w);
	~TileMap(void);
private:
	int height,width;
};

#endif