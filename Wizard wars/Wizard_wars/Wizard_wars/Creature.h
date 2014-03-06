#ifndef Creature_H
#define Creature_H

#include "GameObject.h"
#include "PassiveState.h"
#include "ActiveState.h"

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
	int MaxHp,CurHp;
	int startDam,CurDam;
private:
};
#endif