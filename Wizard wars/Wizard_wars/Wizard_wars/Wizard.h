#ifndef Wizard_H
#define Wizard_H
#include <vector>
#include "GameObject.h"
#include "PassiveState.h"
#include "Spell.h"

class Wizard:public GameObject
{
public:
	Wizard(sf::Vector2<int> pos,int hp,int dam);
	~Wizard();
	int MaxHp,CurHp;
	int startDam,CurDam;
	int AP;
	int APMax;
	Status status;
	bool moving;
	std::vector<Spell> Spells;
};
#endif