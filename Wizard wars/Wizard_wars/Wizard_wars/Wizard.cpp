#include "Wizard.h"

Wizard::Wizard(sf::Vector2<int> pos,Class c):GameObject(pos)
{
	C = c;
	switch (c)
	{
		case WIZARD:
		MaxHp = 20;
		startDam = 2;
		CurHp = MaxHp;
		CurDam = startDam;
		AP = 10;
		APMax = 10;
		Spells.push_back(Spell(ATTACK));
		Spells.push_back(Spell(MAGIC_MISSILE));
		Spells.push_back(Spell(FIREBALL));
		break;

		case NECROMANCER:
		MaxHp = 20;
		startDam = 1;
		CurHp = MaxHp;
		CurDam = startDam;
		AP = 10;
		APMax = 10;
		Spells.push_back(Spell(ATTACK));
		Spells.push_back(Spell(MAGIC_MISSILE));
		Spells.push_back(Spell(RAISE_UNDEAD));
		break;

		case CLERIC:
		MaxHp = 30;
		startDam = 9;
		CurHp = MaxHp;
		CurDam = startDam;
		AP = 10;
		APMax = 10;
		Spells.push_back(Spell(ATTACK));
		Spells.push_back(Spell(MAGIC_MISSILE));
		Spells.push_back(Spell(HEAL));
		break;

		case SUMMONER:
		MaxHp = 30;
		startDam = 9;
		CurHp = MaxHp;
		CurDam = startDam;
		AP = 10;
		APMax = 10;
		Spells.push_back(Spell(ATTACK));
		Spells.push_back(Spell(MAGIC_MISSILE));
		Spells.push_back(Spell(SUMMON_DEMON));
		Spells.push_back(Spell(STONE_WALL));
		break;

		case UNDEAD:
		MaxHp = 20;
		startDam = 10;
		CurHp = MaxHp;
		CurDam = startDam;
		AP = 0;
		APMax = 10;
		Spells.push_back(Spell(ATTACK));
		Spells[0].Cost = 5;


		case DEMON:
		MaxHp = 50;
		startDam = 17;
		CurHp = MaxHp;
		CurDam = startDam;
		AP = 0;
		APMax = 15;
		Spells.push_back(Spell(ATTACK));
		Spells[0].Cost = 5;
		break;

		default:
		MaxHp = 20;
		startDam = 2;
		CurHp = MaxHp;
		CurDam = startDam;
		AP = 10;
		APMax = 10;
		Spells.push_back(Spell(ATTACK));
		Spells.push_back(Spell(MAGIC_MISSILE));
		Spells.push_back(Spell(FIREBALL));
		break;
	}
	status = ALIVE;
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

void Wizard::update()
{
	CurDam = startDam /((CurHp+1/2));
	threat = CurHp+CurDam+APMax+Spells.size();
}