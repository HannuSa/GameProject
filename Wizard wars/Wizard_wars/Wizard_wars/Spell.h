#ifndef Spell_H
#define Spell_H

enum Type
{
	ATTACK = 0,
	MAGIC_MISSILE,
	FIREBALL,
	ICE_BOLT,
	STONE_WALL,
	RAISE_UNDEAD,
	SUMMON_DEMON,
	HEAL
};

class Spell
{
public:
	Spell(Type t);
	~Spell();

	Type type;
	int Cost;
	int Damage;
	bool Selected;
};
#endif