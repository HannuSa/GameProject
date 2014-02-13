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

    /*sf::RenderWindow window(sf::VideoMode(800, 600), "Wizard wars!");

	sf::Texture texture;
	
	texture.loadFromFile("../Resources/Ruoho.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(50, 50));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		window.draw(sprite);
        window.display();
    }
	*/

    return 0;
}
