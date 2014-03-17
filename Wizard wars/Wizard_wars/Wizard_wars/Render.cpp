#include "Render.h"
#include <Windows.h>

Render::Render(Scene *scene)
	:scene(scene)
{
	window.create(sf::VideoMode(1000,600),"Wizard wars");
	Grass.loadFromFile("../Resources/Ruoho.png");
	sprite.setTexture(Grass);
	Test.loadFromFile("../Resources/Guy.png");
	Test1.setTexture(Test);
	goblin.loadFromFile("../Resources/Goblin.png");
	Test2.setTexture(goblin);
	font.loadFromFile("../Resources/firstv2.ttf");
	text.setFont(font);
	text.setColor(sf::Color::Red);

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
	//Sleep(100);
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
				sprite.setPosition(x*32+scene->DrawPos.x,y*32+scene->DrawPos.y);
				window.draw(sprite);
				break;
			}
		}
	}
	std::vector<Creature*>* Temp=scene->GetCreatures();
	std::vector<Wizard*>* Temp2=scene->GetWizards();

	for(int i=0;i<Temp2->size();i++)
	{
		Test1.setPosition(Temp2->at(i)->GetPosition().x*32+scene->DrawPos.x,
				Temp2->at(i)->GetPosition().y*32+scene->DrawPos.y);
			if(Temp2->at(i)->CurHp<Temp2->at(i)->MaxHp)
			{
				Test1.setColor(sf::Color(255,0,0));
			}
			window.draw(Test1);
	}

	for(int i=0;i<Temp->size();i++)
	{
		///*if(Temp->at(i)->GetType()==1)
		//{	
		//	Test1.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
		//		Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
		//	if(Temp->at(i)->CurHp<Temp->at(i)->MaxHp)
		//	{
		//		Test1.setColor(sf::Color(255,0,0));
		//	}
		//	window.draw(Test1);*/
		//}

		if(Temp->at(i)->GetType()==2)
		{
			Test2.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
				Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Test2);
		}

	}

	if(scene->GetState()->returnState() == GROUP_1_TURN)
	{
		window.draw(SpellList);
		for(int i = 0; i < Temp2->size(); i++)
		{
			if(Temp2->at(i)->Selected==true)
				{
				for(int x = 0; x<Temp2->at(i)->Spells.size();x++)
				{
					if(scene->GetWizards()->at(i)->Spells[x]==MAGIC_MISSILE)
					{
						text.setString("Magic Missile");
					}
					text.setPosition(810,0);
					window.draw(text);				
				}
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