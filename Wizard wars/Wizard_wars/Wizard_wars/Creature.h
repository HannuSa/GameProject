#ifndef Creature_H
#define Creature_H

#include "GameObject.h"

class Creature:public GameObject
{
public:
	Creature(sf::Vector2<int> pos,int t);
	~Creature();
	int GetType();
private:
	int type;
};
#endif