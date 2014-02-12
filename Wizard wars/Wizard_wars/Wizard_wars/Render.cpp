#include "Render.h"
#include <SFML/Graphics.hpp>


Render::Render(Scene *scene)
	:scene(scene)
{
	window.create(sf::VideoMode(800,600),"Wizard wars");
	Grass.loadFromFile("../Resources/Ruoho.png");
	sprite.setTexture(Grass);
}


Render::~Render(void)
{
}


void Render::update()
{
	window.clear();

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
				printf("ruohhooo!");
				sprite.setPosition(x*32,y*32);
				window.draw(sprite);
				break;
			}


		}
	}

	
			 while (window.isOpen())
			{
			  sf::Event event;
			 while (window.pollEvent(event))
			{
			 if (event.type == sf::Event::Closed)
                window.close();
			}
			 window.display();
			}
}