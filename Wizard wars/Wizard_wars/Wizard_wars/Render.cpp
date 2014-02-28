#include "Render.h"
#include <Windows.h>

Render::Render(Scene *scene)
	:scene(scene)
{
	window.create(sf::VideoMode(800,600),"Wizard wars");
	Grass.loadFromFile("../Resources/Ruoho.png");
	sprite.setTexture(Grass);
	Test.loadFromFile("../Resources/Guy.png");
	Test1.setTexture(Test);
	goblin.loadFromFile("../Resources/Goblin.png");
	Test2.setTexture(goblin);
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
				sprite.setPosition(x*32+scene->DrawPos.x,y*32+scene->DrawPos.y);
				window.draw(sprite);
				break;
			}
		}
	}
	std::vector<Creature*>* Temp=scene->GetCreatures();
	for(int i=0;i<Temp->size();i++)
	{
		if(Temp->at(i)->GetType()==1)
		{	
			Test1.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
				Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Test1);
		}

		if(Temp->at(i)->GetType()==2)
		{
			Test2.setPosition(Temp->at(i)->GetPosition().x*32+scene->DrawPos.x,
				Temp->at(i)->GetPosition().y*32+scene->DrawPos.y);
			window.draw(Test2);
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