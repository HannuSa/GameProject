#ifndef Input_H
#define Input_H

#include "Scene.h"
#include <SFML\Graphics.hpp>

class Input
{
public:
	Input(Scene *c,sf::RenderWindow *w);
	~Input();

	void Update();
	void MoveMap();
	void Select();
	void Act();
private:
	Scene *scene;
	sf::RenderWindow *window;
};
#endif