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
	Scene *scene = new Scene(c);
	Render render(scene);
	for(;;)
	{
	render.update();
	}

    return 0;
}
