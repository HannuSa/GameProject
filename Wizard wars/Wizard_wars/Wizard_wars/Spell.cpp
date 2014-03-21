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
}

Spell::~Spell()
{
}