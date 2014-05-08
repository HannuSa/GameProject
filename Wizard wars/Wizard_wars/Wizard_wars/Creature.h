#ifndef Creature_H
#define Creature_H

#include "GameObject.h"
#include "PassiveState.h"
#include "ActiveState.h"
#include <vector>

enum Kind
{
	GOBLIN = 0,
	HOBGOBLIN,
	SLUG,
	MINOTAUR,
	IMP,
	CHAOS_SPAWN,
	PARACLYST_1,
	PARACLYST_2,
	PARACLYST_3
};

class Creature:public GameObject
{
public:
	Creature(sf::Vector2<int> pos,Kind t);
	~Creature();
	ActionState action;
	Status status;
	Kind type;
	int AP;
	int APMax;
	int MaxHp,CurHp;
	int startDam,CurDam;
	bool acting;
	void Move();
	void SetPath(std::vector<sf::Vector2<int>> p);
	std::vector<sf::Vector2<int>> path;
private:
	std::vector<sf::Vector2<int>>::iterator it;
};
#endif