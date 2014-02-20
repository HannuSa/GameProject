#include "GameObject.h"

GameObject::GameObject(sf::Vector2<int> pos)
{
	Position = pos;
}

GameObject::~GameObject()
{}

sf::Vector2<int> GameObject::GetPosition()
{
	return Position;
}

void GameObject::Move(sf::Vector2<int> newP)
{
	Position = newP;
}