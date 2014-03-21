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
	bool SetDestination();
	void SelectSpell();
	void CastSpell(Wizard w,Spell s);
private:
	Scene *scene;
	sf::RenderWindow *window;
	sf::Vector2<int> Destination;
};
#endif