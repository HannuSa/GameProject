#ifndef Render_H
#define Render_H
#include "scene.h"
#include <SFML/Graphics.hpp>


class Render :public Scene
{
public:
	Render(Scene *scene);
	~Render(void);

	void update();
	sf::RenderWindow* GetWindow();
private:
	Scene *scene;
	sf::RenderWindow window;
	//Map assets
	sf::Texture grass;
	sf::Sprite Grass;

	sf::Texture fire;
	sf::Sprite Fire;

	//Wizard assets
	sf::Texture wizard;
	sf::Sprite Wizard_;

	sf::Texture cleric;
	sf::Sprite Cleric;

	sf::Texture necromancer;
	sf::Sprite Necromancer;

	sf::Texture summoner;
	sf::Sprite Summoner;

	sf::Texture demon;
	sf::Sprite Demon;

	sf::Texture dead;
	sf::Sprite Dead;
		
	//Enemy assets
	sf::Texture goblin;
	sf::Sprite Goblin;

	sf::Texture hobgoblin;
	sf::Sprite Hobgoblin;

	sf::Texture slug;
	sf::Sprite Slug;

	sf::Texture imp;
	sf::Sprite Imp;

	sf::Texture minotaur;
	sf::Sprite Minotaur;

	sf::Texture freak;
	sf::Sprite Freak;

	sf::Texture stage1;
	sf::Sprite Stage1;

	sf::Texture stage2;
	sf::Sprite Stage2;

	sf::Texture stage3;
	sf::Sprite Stage3;

	//Spell things
	sf::Font font;
	sf::Text text;
	sf::Text ActionPoints;

	sf::RectangleShape SpellList;
};
#endif