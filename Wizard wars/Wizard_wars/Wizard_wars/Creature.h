#ifndef Creature_H
#define Creature_H

#include "GameObject.h"
#include "PassiveState.h"
#include "ActiveState.h"
#include <vector>

class Creature:public GameObject
{
public:
	Creature(sf::Vector2<int> pos,int t,int hp,int dam);
	~Creature();
	int GetType();
	ActionState action;
	Status status;
	int type;
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