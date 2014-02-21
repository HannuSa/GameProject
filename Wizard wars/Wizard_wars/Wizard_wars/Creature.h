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
	int GetAP();
	void UseAP(int A);
private:
	int type;
	int AP;
	int MaxHp,CurHp;
	int startDam,CurDam;
	ActionState action;
	Status status;
};
#endif