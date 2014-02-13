#include "Scene.h"

Scene::Scene()
{}

Scene::Scene(Creature *c)
{
	creatures.push_back(c);
}


Scene::~Scene(void)
{
}
