#include "Wizard.h"

Wizard::Wizard(sf::Vector2<int> pos,int hp,int dam):GameObject(pos)
{
	MaxHp = hp;
	startDam = dam;
	CurHp = MaxHp;
	CurDam = startDam;
	AP = 7;
	status = ALIVE;
}

Wizard::~Wizard()
{}