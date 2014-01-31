#include <SFML/Graphics.hpp>
#include "TileMap.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Wizard wars!");

	const int level[] = 
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0
	};

	TileMap map;
	if(!map.load("../Resources.tileset.png",sf::Vector2u(32,32) , level, 16 ,2))
		return -1;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		window.draw(map);
        window.display();
    }

    return 0;
}
