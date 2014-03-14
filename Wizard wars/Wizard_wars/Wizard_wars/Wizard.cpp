#include "Wizard.h"

Wizard::Wizard(sf::Vector2<int> pos,int hp,int dam):GameObject(pos)
{
	MaxHp = hp;
	startDam = dam;
	CurHp = MaxHp;
	CurDam = startDam;
	AP = 10;
	APMax = 10;
	status = ALIVE;
	Spells.push_back(MAGIC_MISSILE);
}

Wizard::~Wizard()
{}