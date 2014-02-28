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
	//MoveMap();
	Select();

	if(scene->GetState()->returnState() == GROUP_1_TURN)
	{
		if(SetDestination()==true)
		{
		std::vector<Creature*>* Temp=scene->GetCreatures();
		for(int i = 0; i < Temp->size();i++)
			{
				if(Temp->at(i)->Selected==true)
				{
					Temp->at(i)->Move(scene->FindPath(Temp->at(i)->GetPosition(),Destination));
				}
			}
		}
	}
}

void Input::MoveMap()
{
if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) == true)
	{
		sf::Vector2<float>Temp(0,0);
		scene->DrawPos=Temp;
	}

	else if(sf::Mouse::getPosition(*window).x<100)
	{
		scene->DrawPos.x+=15;
	}
	else if(sf::Mouse::getPosition(*window).x>700)
	{
		scene->DrawPos.x-=15;
	}
	else if(sf::Mouse::getPosition(*window).y<100)
	{
		scene->DrawPos.y+=15;
	}
	else if(sf::Mouse::getPosition(*window).y>500)
	{
		scene->DrawPos.y-=15;
	}
}

void Input::Select()
{
	std::vector<Creature*>* Temp=scene->GetCreatures();
	if(scene->GetState()->returnState() == GROUP_1_TURN)
	{
		for(int i = 0; i < Temp->size();i++)
		{
			//Temp->at(i)->Selected=false;
			if(
				Temp->at(i)->GetPosition().x*32 <=sf::Mouse::getPosition(*window).x &&
				sf::Mouse::getPosition(*window).x <=Temp->at(i)->GetPosition().x*32+32 &&

				Temp->at(i)->GetPosition().x*32 <=sf::Mouse::getPosition(*window).y &&
				sf::Mouse::getPosition(*window).y <=Temp->at(i)->GetPosition().y*32+32 )
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)== true)
				{
					Temp->at(i)->Selected=true;
					break;
				}
			}
		}
	}
}

bool Input::SetDestination()
{
	std::vector<Creature*>* Temp=scene->GetCreatures();
		for(int i = 0; i < Temp->size();i++)
		{
			if(Temp->at(i)->Selected==true)
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)==true)
				{
					Destination.x = sf::Mouse::getPosition(*window).x/32;
					Destination.y = sf::Mouse::getPosition(*window).y/32;
					return true;
				}
			}
		}
	return false;
}

void Input::Act()
{
	
}