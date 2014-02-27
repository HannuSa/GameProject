#include "Input.h"

Input::Input(Scene *c,sf::RenderWindow *w)
{
	scene = c;
	window = w;
}

Input::~Input()
{}

void Input::Update()
{
	MoveMap();
}

void Input::MoveMap()
{
if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) == true)
	{
		sf::Vector2<float>Temp(0,0);
		scene->NewPos(Temp);
	}

	else if(sf::Mouse::getPosition(*window).x<100)
	{
		sf::Vector2<float>Temp = scene->GetPos();
		Temp.x+=15;
		scene->NewPos(Temp);
	}
	else if(sf::Mouse::getPosition(*window).x>700)
	{
		sf::Vector2<float>Temp = scene->GetPos();
		Temp.x-=15;
		scene->NewPos(Temp);
	}
	else if(sf::Mouse::getPosition(*window).y<100)
	{
		sf::Vector2<float>Temp = scene->GetPos();
		Temp.y+=15;
		scene->NewPos(Temp);
	}
	else if(sf::Mouse::getPosition(*window).y>500)
	{
		sf::Vector2<float>Temp = scene->GetPos();
		Temp.y-=15;
		scene->NewPos(Temp);
	}
}