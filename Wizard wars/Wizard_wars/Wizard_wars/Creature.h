#ifndef Creature_H
#define Creature_H

#include "GameObject.h"

class Creature:public GameObject
{
public:
	Creature(sf::Vector2<int> pos,int t);
	~Creature();
	int GetType();
	int GetAP();
	void UseAP(bool Use,int A);
private:
	int type;
	int AP;
};
#endif