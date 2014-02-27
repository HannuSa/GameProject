#include <SFML/Graphics.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <iostream>
#include "Tile.h"
#include "TileMap.h"
#include "Creature.h"
#include "Scene.h"
#include "Render.h"
#include "Input.h"

int main()
{
	Creature *c = new Creature(sf::Vector2<int>(1,1),1,20,5);
	Creature *c1 = new Creature(sf::Vector2<int>(5,5),2,4,2);
	Scene scene(c);
	scene.AddCreature(c1);
	Render render(&scene);
	Input input(&scene,render.GetWindow());
	for(;;)
	{
		input.Update();
		scene.update();
		render.update();
	}

    return 0;
}
