#ifndef GameObject_H
#define GameObject_H
#include <SFML\System\Vector2.hpp>

class GameObject
{
public:
	GameObject(sf::Vector2<int> pos);
	virtual ~GameObject();
	sf::Vector2<int> GetPosition();
	virtual void Move(sf::Vector2<int> newP);
	bool Selected;
protected:
	sf::Vector2<int> Position;
};
#endif