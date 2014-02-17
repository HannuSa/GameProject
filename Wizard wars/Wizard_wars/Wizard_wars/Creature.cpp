#include "Creature.h"

Creature::Creature(sf::Vector2<int> pos,int t):GameObject(pos)
{
	type = t;
	AP = 7;
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



void Creature::UseAP(bool Use,int A)
{
	if (Use == true)
	{
		AP-=A;
	}
	else
	{
		AP+=A;
	}
}