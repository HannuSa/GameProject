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

	Wizard *w = new Wizard(sf::Vector2<int>(1,9),WIZARD);
	Scene scene(w);

	Creature *c1 = new Creature(sf::Vector2<int>(1,4),GOBLIN);
	Creature *c2 = new Creature(sf::Vector2<int>(2,4),HOBGOBLIN);
	Creature *c3 = new Creature(sf::Vector2<int>(3,4),SLUG);
	Creature *c4 = new Creature(sf::Vector2<int>(4,4),MINOTAUR);
	Creature *c5 = new Creature(sf::Vector2<int>(5,4),IMP);
	Creature *c6 = new Creature(sf::Vector2<int>(6,4),CHAOS_SPAWN);
	Creature *c7 = new Creature(sf::Vector2<int>(7,4),PARACLYST_1);
	Creature *c8 = new Creature(sf::Vector2<int>(8,4),PARACLYST_2);
	Creature *c9 = new Creature(sf::Vector2<int>(9,4),PARACLYST_3);
	Creature *c10 = new Creature(sf::Vector2<int>(4,7),GOBLIN);

	scene.AddCreature(c1);
	scene.AddCreature(c2);
	scene.AddCreature(c3);
	scene.AddCreature(c4);
	scene.AddCreature(c5);
	scene.AddCreature(c6);
	scene.AddCreature(c7);
	scene.AddCreature(c8);
	scene.AddCreature(c9);
	scene.AddCreature(c10);

	Wizard *w2 = new Wizard(sf::Vector2<int>(2,9),NECROMANCER);
	Wizard *w3 = new Wizard(sf::Vector2<int>(3,9),CLERIC);
	Wizard *w4 = new Wizard(sf::Vector2<int>(4,9),SUMMONER);
	Wizard *w5 = new Wizard(sf::Vector2<int>(5,9),UNDEAD);
	Wizard *w6 = new Wizard(sf::Vector2<int>(6,9),DEMON);

	scene.AddWizard(w2);
	scene.AddWizard(w3);
	scene.AddWizard(w4);
	scene.AddWizard(w5);
	scene.AddWizard(w6);

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