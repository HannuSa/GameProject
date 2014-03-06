#ifndef Scene_H
#define Scene_H
#include "TileMap.h"
#include "Creature.h"
#include "Wizard.h"
#include "GameState.h"
#include <vector>
class Scene
{
public:
	Scene();
	Scene(Wizard *w);
	~Scene(void);
	void AddCreature(Creature *c);
	void update();
	bool CheckTurnEnd();
	void MoveCreature(int T);

	sf::Vector2<float> DrawPos;
	GameState *GetState();

	TileType GetTileByPos(sf::Vector2<int> Pos);
	sf::Vector2<int> GetTargetPos();
	double GetDistance(sf::Vector2<int> Target, sf::Vector2<int> Begin);

	void Attack(Creature* Attacker, Wizard* Target);
	
	sf::Vector2<int> FindPath(sf::Vector2<int> Start,sf::Vector2<int> End);
protected:
	GameState *CurrentState;
	TileMap tilemap;
	std::vector<Creature*> Creatures;
	std::vector<Wizard*> Wizards;
public:
	TileMap* getTilemap()
	{
		return &tilemap;
	}
	std::vector<Creature*>* GetCreatures()
	{
		return &Creatures;
	}
	std::vector<Wizard*>* GetWizards()
	{
		return &Wizards;
	}
};

#endif