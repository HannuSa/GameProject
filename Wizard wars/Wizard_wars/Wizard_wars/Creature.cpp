#include "Creature.h"

Creature::Creature(sf::Vector2<int> pos,int t,int hp,int dam):GameObject(pos)
{
	type = t;
	AP = 7;
	APMax = 7;
	MaxHp = hp;
	startDam = dam;
	CurHp = MaxHp;
	CurDam = startDam;
	action = SEEK;
	status = ALIVE;
	acting = false;
}

Creature::~Creature()
{}

int Creature::GetType()
{
	return type;
}
