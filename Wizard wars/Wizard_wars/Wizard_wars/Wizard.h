#ifndef Wizard_H
#define Wizard_H
#include "GameObject.h"
#include "PassiveState.h"

class Wizard:public GameObject
{
public:
	Wizard(sf::Vector2<int> pos,int hp,int dam);
	~Wizard();
	int MaxHp,CurHp;
	int startDam,CurDam;
	int AP;
	Status status;
};
#endif