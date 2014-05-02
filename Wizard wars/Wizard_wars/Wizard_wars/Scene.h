#ifndef Scene_H
#define Scene_H
#include "TileMap.h"
#include "Creature.h"
#include "Wizard.h"
#include "GameState.h"
#include "SpellManager.h"
#include "SearchNode.h"
#include <vector>

struct Target
{
	Wizard *W;
	Creature *C;
};

class Scene
{
public:
	Scene();
	Scene(Wizard *w);
	~Scene(void);
	void AddCreature(Creature *c);
	void AddWizard(Wizard *w);
	void AddObject(GameObject *g);
	void update();
	bool CheckTurnEnd();
	void MoveCreature(Creature *c);

	sf::Vector2<float> DrawPos;
	GameState *GetState();

	TileType GetTileByPos(sf::Vector2<int> Pos);
	sf::Vector2<int> GetTargetPos();
	double GetDistance(sf::Vector2<int> Target, sf::Vector2<int> Begin);

	void Attack(Creature* Attacker, Wizard* Target);
	
	//Pathfinding
	SearchNode* getNextNode();
	std::vector<sf::Vector2<int>> FindPath(sf::Vector2<int> Start,sf::Vector2<int> End);
	std::vector<sf::Vector2<int>> FindPathReversed(sf::Vector2<int> Start,sf::Vector2<int> End);
	void clearVectors();
	void pathOpened(sf::Vector2<int> Position, float newCost,SearchNode* nextNode, SearchNode* goalNode);


	Target *GetCreatureByPos(sf::Vector2<int> P);

	SpellManager s;
	//Input and render
	Wizard *Selected;

protected:
	GameState *CurrentState;
	TileMap tilemap;
	std::vector<Creature*> Creatures;
	std::vector<Creature*>::iterator Indicator;
	std::vector<Wizard*> Wizards;
	std::vector<GameObject*> Objects;


	//Components for pathfinding
	std::vector<SearchNode*> openList;
	std::vector<SearchNode*> closedList;
	std::vector<sf::Vector2<int>> PathToGoal;

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