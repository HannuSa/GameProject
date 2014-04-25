#ifndef Wizard_H
#define Wizard_H
#include <vector>
#include "GameObject.h"
#include "PassiveState.h"
#include "Spell.h"

class Wizard:public GameObject
{
public:
	Wizard(sf::Vector2<int> pos,int hp,int dam);
	~Wizard();
	void AddSpell(Spell s);
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