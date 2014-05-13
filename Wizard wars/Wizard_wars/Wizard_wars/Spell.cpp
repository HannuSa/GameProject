#include "Spell.h"

Spell::Spell(Type t)
{
	type = t;
	Cost = 0;
	Damage = 0;
	Selected = false;

	if(type == ATTACK)
	{
		Cost = 1;
		Damage = 0;
	}
	else if(type == MAGIC_MISSILE)
	{
		Cost = 2;
		Damage = 4;
	}
	else if(type == FIREBALL)
	{
		Cost = 4;
		Damage = 8;
	}
	else if(type == ICE_BOLT)
	{
		Cost = 3;
		Damage = 2;
	}
	else if(type == STONE_WALL)
	{
		Cost = 4;
		Damage = 0;
	}
	else if(type == RAISE_UNDEAD)
	{
		Cost = 5;
		Damage = 0;
	}
	else if(type == SUMMON_DEMON)
	{
		Cost = 8;
		Damage = 0;
	}
	else if(type == HEAL)
	{
		Cost = 4;
		Damage = 0;
	}

}

Spell::~Spell()
{
}