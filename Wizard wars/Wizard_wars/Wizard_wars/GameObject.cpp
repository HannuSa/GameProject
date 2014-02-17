#include "GameObject.h"

GameObject::GameObject(sf::Vector2<int> pos)
{
	Position = pos;
}

GameObject::~GameObject()
{}

int GameObject::getX()
{
	return Position.x;
}

int GameObject::getY()
{
	return Position.y;
}

void GameObject::Move(int X,int Y)
{
	Position.x+=X;
	Position.y+=Y;
}