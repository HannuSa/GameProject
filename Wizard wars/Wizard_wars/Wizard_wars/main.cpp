#include <SFML/Graphics.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <iostream>
#include "Tile.h"
#include "TileMap.h"
#include "Creature.h"
#include "Scene.h"
#include "Render.h"

int main()
{
	Creature *c = new Creature(sf::Vector2<int>(1,1),1);
	Creature *c1 = new Creature(sf::Vector2<int>(5,5),2);
	Scene *scene = new Scene(c);
	scene->AddCreature(c1);
	Render render(scene);
	for(;;)
	{
	render.update();
	}

    return 0;
}
