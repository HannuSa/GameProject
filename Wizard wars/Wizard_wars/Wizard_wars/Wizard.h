#ifndef Wizard_H
#define Wizard_H
#include <vector>
#include "GameObject.h"
#include "PassiveState.h"
#include "Spell.h"

enum Class
{
	WIZARD = 0,
	NECROMANCER,
	CLERIC,
	SUMMONER,
	DEMON,
};

class Wizard:public GameObject
{
public:
	Wizard(sf::Vector2<int> pos,Class c);
	~Wizard();
	void AddSpell(Spell s);
	Class C;
	int MaxHp,CurHp;
	int startDam,CurDam;
	int AP;
	int APMax;
	Status status;
	bool moving;
	std::vector<Spell> Spells;
	void Move();
	void SetPath(std::vector<sf::Vector2<int>> p);
	std::vector<sf::Vector2<int>> path;
private:
	std::vector<sf::Vector2<int>>::iterator it;
};
#endif