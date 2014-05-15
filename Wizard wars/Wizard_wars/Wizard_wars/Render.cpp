#include "Render.h"
#include <Windows.h>
#include <string>
#include <sstream>


Render::Render(Scene *scene)
	:scene(scene)
{
	window.create(sf::VideoMode(1000,600),"Wizard wars");
	//Tile map assets
	grass.loadFromFile("../Resources/Ruoho.png");
	Grass.setTexture(grass);
	fire.loadFromFile("../Resources/RuohoFire.png");
	Fire.setTexture(fire);

	//Wizard assets
	wizard.loadFromFile("../Resources/Guy.png");
	Wizard_.setTexture(wizard);
	cleric.loadFromFile("../Resources/Cleric.png");
	Cleric.setTexture(cleric);
	necromancer.loadFromFile("../Resources/Necromancer.png");
	Necromancer.setTexture(necromancer);
	summoner.loadFromFile("../Resources/Summoner.png");
	Summoner.setTexture(summoner);
	demon.loadFromFile("../Resources/Demon.png");
	Demon.setTexture(demon);
	dead.loadFromFile("../Resources/P_Dead.png");
	Dead.setTexture(dead);

	//Enemy assets
	goblin.loadFromFile("../Resources/Goblin.png");
	Goblin.setTexture(goblin);
	hobgoblin.loadFromFile("../Resources/HobGoblin.png");
	Hobgoblin.setTexture(hobgoblin);
	slug.loadFromFile("../Resources/Slug.png");
	Slug.setTexture(slug);
	imp.loadFromFile("../Resources/Imp.png");
	Imp.setTexture(imp);
	minotaur.loadFromFile("../Resources/Minotaur.png");
	Minotaur.setTexture(minotaur);
	freak.loadFromFile("../Resources/Freak.png");
	Freak.setTexture(freak);
	stage1.loadFromFile("../Resources/Stage1.png");
	Stage1.setTexture(stage1);
	stage2.loadFromFile("../Resources/Stage2.png");
	Stage2.setTexture(stage2);
	stage3.loadFromFile("../Resources/Stage3.png");
	Stage3.setTexture(stage3);


	//Spell things
	font.loadFromFile("../Resources/firstv2.ttf");
	text.setFont(font);
	text.setColor(sf::Color::Red);

	ActionPoints.setFont(font);
	ActionPoints.setColor(sf::Color::Red);
	ActionPoints.setPosition(810,550);

	SpellList.setSize(sf::Vector2f(200,600));
	SpellList.setPosition(800,0);
	SpellList.setFillColor(sf::Color(150,75,0));
}


Render::~Render(void)
{
}

sf::RenderWindow* Render::GetWindow()
{
	return &window;
}

void Render::update()
{
	window.clear();
	Sleep(100);
	for(int x = 0; x < TILEMAP_WIDTH; ++x)
	{
		for(int y = 0; y < TILEMAP_HEIGHT; ++y)
		{


			switch(scene->getTilemap()->tiles[x][y])
			{
			case TILE_VOID:
				printf("invalid tile type!");
				break;
			case TILE_GRASS:
				Grass.setPosition(x*32+scene->DrawPos.x,y*32+scene->DrawPos.y);
				window.draw(Grass);
				break;
			case TILE_FIRE:
				Fire.setPosition(x*32+scene->DrawPos.x,y*32+scene->DrawPos.y);
				window.draw(Fire);
				break;
			}
		}
	}
	std::vector<Creature*>* Temp=scene->GetCreatures();
	std::vector<Wizard*>* Temp2=scene->GetWizards();

	for(int i=0;i<Temp2->size();i++)
	{
		switch (Temp2->at(i)->C)
		{	
			case WIZARD:
			Wizard_.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp2->at(i)->CurHp<Temp2->at(i)->MaxHp)
			{
				Wizard_.setColor(sf::Color(255,0,0));
			}
			else if(Temp2->at(i)->status == FROZEN)
			{
				Wizard_.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Wizard_.setColor(sf::Color(255, 255, 255));
			}
			if(Temp2->at(i)->status != DEAD)
			{
				window.draw(Wizard_);
			}
			else
			{
			Dead.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			Necromancer.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp2->at(i)->CurHp<Temp2->at(i)->MaxHp)
			{
				Necromancer.setColor(sf::Color(255,0,0));
			}
			else if(Temp2->at(i)->status == FROZEN)
			{
				Necromancer.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Necromancer.setColor(sf::Color(255, 255, 255));
			}
			if(Temp2->at(i)->status != DEAD)
			{
				window.draw(Necromancer);
			}
			else
			{
			Dead.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case CLERIC:
			Cleric.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp2->at(i)->CurHp<Temp2->at(i)->MaxHp)
			{
				Cleric.setColor(sf::Color(255,0,0));
			}
			else if(Temp2->at(i)->status == FROZEN)
			{
				Cleric.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Cleric.setColor(sf::Color(255, 255, 255));
			}
			if(Temp2->at(i)->status != DEAD)
			{
				window.draw(Cleric);
			}
			else
			{
			Dead.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case SUMMONER:
			Summoner.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp2->at(i)->CurHp<Temp2->at(i)->MaxHp)
			{
				Summoner.setColor(sf::Color(255,0,0));
			}
			else if(Temp2->at(i)->status == FROZEN)
			{
				Summoner.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Summoner.setColor(sf::Color(255, 255, 255));
			}
			if(Temp2->at(i)->status != DEAD)
			{
					window.draw(Summoner);
			}
			else
			{
			Dead.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case DEMON:
			Demon.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp2->at(i)->status == FROZEN)
			{
				Demon.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Demon.setColor(sf::Color(255, 255, 255));
			}
			if(Temp2->at(i)->status != DEAD)
			{
				window.draw(Demon);
			}
			else
			{
			Dead.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			default:
			Wizard_.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp2->at(i)->CurHp<Temp2->at(i)->MaxHp)
			{
				Wizard_.setColor(sf::Color(255,0,0));
			}
			else if(Temp2->at(i)->status == FROZEN)
			{
				Wizard_.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Wizard_.setColor(sf::Color(255, 255, 255));
			}
			if(Temp2->at(i)->status != DEAD)
			{
				window.draw(Wizard_);
			}
			else
			{
			Dead.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;
		}
	}

	for(int i=0;i<Temp->size();i++)
	{
		switch (Temp->at(i)->type)
		{
			case GOBLIN:
			Goblin.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
			{
				Goblin.setColor(sf::Color(255,0,0));
			}
			else if(Temp->at(i)->status == FROZEN)
			{
				Goblin.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Goblin.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
				window.draw(Goblin);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;
			
			case HOBGOBLIN:
			Hobgoblin.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
			{
				Hobgoblin.setColor(sf::Color(255,0,0));
			}
			else if(Temp->at(i)->status == FROZEN)
			{
				Hobgoblin.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Hobgoblin.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
			window.draw(Hobgoblin);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
				window.draw(Dead);
			}
			break;

			case SLUG:
			Slug.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
			{
				Slug.setColor(sf::Color(255,0,0));
			}
			else if(Temp->at(i)->status == FROZEN)
			{
				Slug.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Slug.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
				window.draw(Slug);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case MINOTAUR:
			Minotaur.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
			{
				Minotaur.setColor(sf::Color(255,0,0));
			}
			else if(Temp->at(i)->status == FROZEN)
			{
				Minotaur.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Minotaur.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
				window.draw(Minotaur);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case IMP:
			Imp.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->status == FROZEN)
			{
				Imp.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Imp.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
				window.draw(Imp);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case CHAOS_SPAWN:
			Freak.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
			{
				Freak.setColor(sf::Color(255,0,0));
			}
			else if(Temp->at(i)->status == FROZEN)
			{
				Freak.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Freak.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
				window.draw(Freak);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case PARACLYST_1:
			Stage1.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
			{
				Stage1.setColor(sf::Color(255,0,0));
			}
			else if(Temp->at(i)->status == FROZEN)
			{
				Stage1.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Stage1.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
				window.draw(Stage1);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case PARACLYST_2:
			Stage2.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
			{
				Stage2.setColor(sf::Color(255,0,0));
			}
			else if(Temp->at(i)->status == FROZEN)
			{
				Stage2.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Stage2.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
				window.draw(Stage2);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

			case PARACLYST_3:
			Stage3.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
			{
				Stage3.setColor(sf::Color(255,0,0));
			}
			else if(Temp->at(i)->status == FROZEN)
			{
				Stage3.setColor(sf::Color(0, 0, 255));
			}
			else
			{
				Stage3.setColor(sf::Color(255, 255, 255));
			}
			if(Temp->at(i)->status != DEAD)
			{
				window.draw(Stage3);
			}
			else
			{
			Dead.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
			Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Dead);
			}
			break;

		}

	}

	if(scene->GetState()->returnState() == GROUP_1_TURN)
	{
		Wizard* chosen = scene->Selected;
		window.draw(SpellList);
			if(chosen != NULL)
				{
				for(int x = 0; x<chosen->Spells.size();x++)
				{
					if(chosen->Spells[x].type==MAGIC_MISSILE)
					{
						text.setString("1)Magic Missile");
						if(chosen->Spells[x].Selected == true)
						{
						text.setString("Magic Missile");
						}
						text.setPosition(810,0+x*25);
						window.draw(text);
					}

					else if(chosen->Spells[x].type==FIREBALL)
					{
						text.setString("2)Fireball");
						if(chosen->Spells[x].Selected == true)
						{
						text.setString("Fireball");
						}
						text.setPosition(810,(0+x*25));
						window.draw(text);
					}
					

					std::stringstream ss;
					ss<<chosen->AP;
					ActionPoints.setString(ss.str());	
					window.draw(ActionPoints);
				}
			}
	}

			 window.display();
			 if (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
						window.close();
					}
			}
}