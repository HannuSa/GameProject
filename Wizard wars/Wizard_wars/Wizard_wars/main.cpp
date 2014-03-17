#include <SFML/Graphics.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <iostream>
#include "Tile.h"
#include "TileMap.h"
#include "Creature.h"
#include "Wizard.h"
#include "Scene.h"
#include "Render.h"
#include "Input.h"

int main()
{
	Wizard *w = new Wizard(sf::Vector2<int>(4,15),20,5);
	Creature *c1 = new Creature(sf::Vector2<int>(1,1),2,4,2);
	Creature *c2 = new Creature(sf::Vector2<int>(2,2),2,4,2);

	Scene scene(w);

	for(int x = 10 ; x > 0; --x){
		for (int y = 10; y > 0; --y){
			Creature *sdfg = new Creature(sf::Vector2<int>(x,y),2,4,2);
			scene.AddCreature(sdfg);
		}
	}
	


	scene.AddCreature(c1);
	scene.AddCreature(c2);
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