#ifndef GameObject_H
#define GameObject_H
#include <SFML\System\Vector2.hpp>

class GameObject
{
public:
	GameObject(sf::Vector2<int> pos);
	virtual ~GameObject();
	int getX();
	int getY();
private:
	sf::Vector2<int> Position;
};
#endif