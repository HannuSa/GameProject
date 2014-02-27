#ifndef GameObject_H
#define GameObject_H
#include <SFML\System\Vector2.hpp>

class GameObject
{
public:
	GameObject(sf::Vector2<int> pos);
	virtual ~GameObject();
	sf::Vector2<int> GetPosition();
	void Move(sf::Vector2<int> newP);
	bool GetSelected();
	void SetSelected(bool s);
protected:
	sf::Vector2<int> Position;
	bool Selected;
};
#endif