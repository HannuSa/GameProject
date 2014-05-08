#include "Creature.h"

Creature::Creature(sf::Vector2<int> pos,Kind t):GameObject(pos)
{
	type = t;
	AP = 7;
	APMax = 7;
	switch (t)
	{
		case GOBLIN:
		MaxHp = 4;
		startDam = 2;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		case HOBGOBLIN:
		MaxHp = 10;
		startDam = 5;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		case SLUG:
		MaxHp =15;
		startDam = 4;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		case MINOTAUR:
		MaxHp = 30;
		startDam = 10;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		case IMP:
		MaxHp = 7;
		startDam = 3;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		case CHAOS_SPAWN:
		MaxHp = 25;
		startDam = 2;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		case PARACLYST_1:
		MaxHp = 5;
		startDam = 2;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		case PARACLYST_2:
		MaxHp = 10;
		startDam = 7;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		case PARACLYST_3:
		MaxHp = 25;
		startDam = 15;
		CurHp = MaxHp;
		CurDam = startDam;
		break;
		default:

		break;
	}
	action = SEEK;
	status = ALIVE;
	acting = false;
}

Creature::~Creature()
{}

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