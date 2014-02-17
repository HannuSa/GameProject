#ifndef Render_H
#define Render_H
#include "scene.h"
class Render :public Scene
{
public:
	Render(Scene *scene);
	~Render(void);

	void update();

private:
	Scene *scene;
	sf::RenderWindow window;
	sf::Texture Grass;
	sf::Texture Test;
	sf::Texture goblin;
	sf::Sprite sprite;
	sf::Sprite Test1;
	sf::Sprite Test2;
};

#endif