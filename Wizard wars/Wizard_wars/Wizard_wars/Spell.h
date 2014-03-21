#ifndef Spell_H
#define Spell_H

enum Type
{
	MAGIC_MISSILE = 0,
	FIREBALL,
	ICE_BOLT,
	STONE_WALL
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