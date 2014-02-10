#ifndef Scene_H
#define Scene_H
#include "TileMap.h"
class Scene
{
public:
	Scene(void);
	~Scene(void);
protected:
	TileMap tilemap;

public:
	TileMap* getTilemap()
	{
		return &tilemap;
	}
};

#endif