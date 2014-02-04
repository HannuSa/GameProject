#include <SFML/Graphics.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <iostream>
#include "Tile.h"
#include "TileMap.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Wizard wars!");

	sf::Texture texture;
	
	if (!texture.loadFromFile("../Resources/Ruoho.png"))
	{
		std::cout<<"Failure to load";
	}

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

    return 0;
}
