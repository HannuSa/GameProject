#ifndef Scene_H
#define Scene_H
#include "TileMap.h"
#include "Creature.h"
#include "GameState.h"
#include <vector>
class Scene
{
public:
	Scene();
	Scene(Creature *c);
	~Scene(void);
	void AddCreature(Creature *c);
	void update();
	void MoveCreature();

	void NewPos(sf::Vector2<float> N);
	sf::Vector2<float> GetPos();

	GameState *GetState();

	TileType GetTileByPos(sf::Vector2<int> Pos);
	sf::Vector2<int> FindPath(sf::Vector2<int> Start,sf::Vector2<int> End);
protected:
	GameState *CurrentState;
	TileMap tilemap;
	sf::Vector2<float> DrawPos;
	std::vector<Creature*> Creatures;
public:
	TileMap* getTilemap()
	{
		return &tilemap;
	}
	std::vector<Creature*>* GetCreatures()
	{
		return &Creatures;
	}
};

#endif