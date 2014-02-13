#ifndef Scene_H
#define Scene_H
#include "TileMap.h"
#include "Creature.h"
#include <vector>
class Scene
{
public:
	Scene();
	Scene(Creature *c);
	~Scene(void);
protected:
	TileMap tilemap;
	std::vector<Creature*> creatures;
public:
	TileMap* getTilemap()
	{
		return &tilemap;
	}
	std::vector<Creature*>* GetCreatures()
	{
		return &creatures;
	}
};

#endif