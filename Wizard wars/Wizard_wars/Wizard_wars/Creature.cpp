#include "Creature.h"

Creature::Creature(sf::Vector2<int> pos,int t):GameObject(pos)
{
	type = t;
}

Creature::~Creature()
{}

int Creature::GetType()
{
	return type;
}