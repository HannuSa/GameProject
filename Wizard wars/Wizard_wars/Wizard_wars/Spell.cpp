#include "Spell.h"

Spell::Spell(Type t)
{
	type = t;
	Cost = 0;
	Damage = 0;
	Selected = false;

	if(type == MAGIC_MISSILE)
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

}

Spell::~Spell()
{
}