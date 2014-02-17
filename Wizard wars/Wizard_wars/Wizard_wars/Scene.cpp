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

void Scene::AddCreature(Creature *c)
{
	creatures.push_back(c);
}

void Scene::update()
{

}