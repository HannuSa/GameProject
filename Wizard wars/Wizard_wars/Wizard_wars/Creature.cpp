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

void Creature::SetPath(std::vector<sf::Vector2<int>> p)
{
	path = p;
	it = path.end();
}

void Creature::Move()
{
	if(!path.empty())
	{
		if(it != path.begin())
		{
			it--;
		}
		GameObject::Move((*it));
	}
}