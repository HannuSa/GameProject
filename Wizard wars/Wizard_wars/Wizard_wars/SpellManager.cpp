#include "SpellManager.h"

SpellManager::SpellManager()
{

}

SpellManager::~SpellManager()
{

}

int SpellManager::CheckCost(Spell s)
{
	int cost = 0;
	if(s == MAGIC_MISSILE)
	{
		cost = 2;
	}
	return cost;
}

int SpellManager::CheckDamage(Spell s)
{
	int damage = 0;

	if(s == MAGIC_MISSILE)
	{
		damage = 4;
	}
	return damage;
}