#ifndef SpellManager_H
#define SpellManager_H
#include "Spell.h"
class SpellManager
{
public:
	SpellManager();
	~SpellManager();
	int CheckCost(Spell s);
	int CheckDamage(Spell S);
};
#endif