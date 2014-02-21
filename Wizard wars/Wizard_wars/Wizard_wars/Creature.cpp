#include "Creature.h"

Creature::Creature(sf::Vector2<int> pos,int t,int hp,int dam):GameObject(pos)
{
	type = t;
	AP = 7;
	MaxHp = hp;
	startDam = dam;
	CurHp = MaxHp;
	CurDam = startDam;
	action = SEEK;
	status = ALIVE;
}

Creature::~Creature()
{}

int Creature::GetType()
{
	return type;
}

int Creature::GetAP()
{
	return AP;
}

void Creature::UseAP(int A)
{
	if(A <= AP)
	{
		AP -= A;
	}
}