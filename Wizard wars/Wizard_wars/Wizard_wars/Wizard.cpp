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
	Spells.push_back(Spell(MAGIC_MISSILE));
	Spells.push_back(Spell(FIREBALL));
}

Wizard::~Wizard()
{}

void Wizard::AddSpell(Spell s)
{
	Spells.push_back(Spell(s));
}

void Wizard::SetPath(std::vector<sf::Vector2<int>> p)
{
	path = p;
	it = path.end();
}

void Wizard::Move()
{
	if(!path.empty())
	{
		if(it != path.begin())
		{
			it--;
		}
		GameObject::Move((*it));
	}
}