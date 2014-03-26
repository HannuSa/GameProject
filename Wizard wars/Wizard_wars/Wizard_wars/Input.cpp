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
	std::vector<Wizard*>* Temp=scene->GetWizards();
	//MoveMap();
	Select();
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true)
	{
		scene->GetState()->NewState(GROUP_2_TURN);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		scene->GetState()->NewState(GROUP_1_TURN);
	}


	if(scene->GetState()->returnState() == GROUP_1_TURN && scene->CheckTurnEnd() == false)
	{
		SelectSpell();
		if(SetDestination()==true)
		{
			for(int i = 0; i < Temp->size();i++)
			{
				if(Temp->at(i)->AP>0)
				{
					if(Temp->at(i)->GetPosition() !=Destination)
					{
						if(Temp->at(i)->Selected==true)
						{
							Temp->at(i)->Move(scene->FindPath(Temp->at(i)->GetPosition(),Destination));
							Temp->at(i)->AP-=1;
							
						}
					}
					if(Temp->at(i)->Selected==true && Temp->at(i)->Spells[0].Selected==true)
					{
						CastSpell(Temp->at(i),Temp->at(i)->Spells[0]);
					}
				}
			}
		}
	}

	else if(scene->GetState()->returnState() == GROUP_1_TURN && scene->CheckTurnEnd() == true)
	{
		for(int i = 0; i<scene->GetWizards()->size();i++)
		{
			Temp->at(i)->AP+=scene->GetWizards()->at(i)->APMax;
			Temp->at(i)->Spells[0].Selected=false;
			Temp->at(i)->moving=false;
			//Temp->at(i)->Selected=false;
		}
		scene->GetState()->NewState(GROUP_2_TURN);
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
	std::vector<Wizard*>* Temp=scene->GetWizards();
	sf::Vector2<float> draw = scene->DrawPos;
	if(scene->GetState()->returnState() == GROUP_1_TURN)
	{
		for(int i = 0; i < Temp->size();i++)
		{
			if(Temp->at(i)->status != DEAD)
			{
				if(
					Temp->at(i)->GetPosition().x*32 <= sf::Mouse::getPosition(*window).x-draw.x &&
					sf::Mouse::getPosition(*window).x-draw.x <= Temp->at(i)->GetPosition().x*32+32 &&

					Temp->at(i)->GetPosition().y*32 <= sf::Mouse::getPosition(*window).y-draw.y &&
					sf::Mouse::getPosition(*window).y-draw.y <= Temp->at(i)->GetPosition().y*32+32 )
				{
					if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)== true)
					{
						Temp->at(i)->Selected=true;
					}
				}
			}
		}
	}
}

bool Input::SetDestination()
{
	sf::Vector2<float> draw = scene->DrawPos;
	std::vector<Wizard*>* Temp=scene->GetWizards();
		for(int i = 0; i < Temp->size();i++)
		{
			if(Temp->at(i)->Selected==true)
			{

				if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)==true)
				{
					Destination.x = (int)((sf::Mouse::getPosition(*window).x-draw.x)/32);
					Destination.y = (int)((sf::Mouse::getPosition(*window).y-draw.y)/32);
					Temp->at(i)->moving=true;
					return true;
				}

				if(Temp->at(i)->moving==true)
				{
					return true;
				}
			}
		}
	return false;
}

void Input::SelectSpell()
{
	std::vector<Wizard*>* Temp=scene->GetWizards();
	for(int i = 0; i < Temp->size();i++)
		{
			if(Temp->at(i)->Selected==true)
			{
				if(Temp->at(i)->Spells[0].type == /*FIREBALL*/MAGIC_MISSILE && sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				{
					if(Temp->at(i)->AP >= Temp->at(i)->Spells[0].Cost)
					{
						Temp->at(i)->Spells[0].Selected=true;
					}
					else 
					{
						printf("Not enough actionpoints");
					}
				}
			}
		}
}

void Input::CastSpell(Wizard *w,Spell s)
{
	sf::Vector2i nakki = sf::Mouse::getPosition(*window);
	sf::Vector2<float> draw = scene->DrawPos;

	nakki.x += draw.x;
	nakki.y += draw.y;

	if(s.type == MAGIC_MISSILE)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if(scene->GetCreatureByPos(nakki/32)->C !=NULL)
			{
				scene->GetCreatureByPos(nakki/32)->C->CurHp -= s.Damage;
				w->AP -= s.Cost;
			}
			else if(scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->W != NULL)
			{
				scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->W->CurHp =- s.Damage;
				w->AP -= s.Cost;
			}
		}
	}

	else if(s.type == FIREBALL)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if(scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->C !=NULL)
			{
				Creature *c = scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->C;
				c->CurHp =- s.Damage;
				scene->getTilemap()->tiles[c->GetPosition().x][c->GetPosition().y]=TILE_FIRE;
				scene->getTilemap()->tiles[c->GetPosition().x+1][c->GetPosition().y]=TILE_FIRE;
				scene->getTilemap()->tiles[c->GetPosition().x+1][c->GetPosition().y+1]=TILE_FIRE;
				scene->getTilemap()->tiles[c->GetPosition().x][c->GetPosition().y+1]=TILE_FIRE;
				scene->getTilemap()->tiles[c->GetPosition().x-1][c->GetPosition().y]=TILE_FIRE;
				scene->getTilemap()->tiles[c->GetPosition().x-1][c->GetPosition().y-1]=TILE_FIRE;
				scene->getTilemap()->tiles[c->GetPosition().x][c->GetPosition().y-1]=TILE_FIRE;
				scene->getTilemap()->tiles[c->GetPosition().x+1][c->GetPosition().y-1]=TILE_FIRE;
				scene->getTilemap()->tiles[c->GetPosition().x-1][c->GetPosition().y+1]=TILE_FIRE;
				w->AP -= s.Cost;
			}
			else if(scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->W != NULL)
			{
				Wizard *w2 = scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->W;
				w2->CurHp =- s.Damage;
				scene->getTilemap()->tiles[w2->GetPosition().x][w2->GetPosition().y]=TILE_FIRE;
				scene->getTilemap()->tiles[w2->GetPosition().x+1][w2->GetPosition().y]=TILE_FIRE;
				scene->getTilemap()->tiles[w2->GetPosition().x+1][w2->GetPosition().y+1]=TILE_FIRE;
				scene->getTilemap()->tiles[w2->GetPosition().x][w2->GetPosition().y+1]=TILE_FIRE;
				scene->getTilemap()->tiles[w2->GetPosition().x-1][w2->GetPosition().y]=TILE_FIRE;
				scene->getTilemap()->tiles[w2->GetPosition().x-1][w2->GetPosition().y-1]=TILE_FIRE;
				scene->getTilemap()->tiles[w2->GetPosition().x][w2->GetPosition().y-1]=TILE_FIRE;
				scene->getTilemap()->tiles[w2->GetPosition().x+1][w2->GetPosition().y-1]=TILE_FIRE;
				scene->getTilemap()->tiles[w2->GetPosition().x-1][w2->GetPosition().y+1]=TILE_FIRE;
				w->AP -= s.Cost;
			}
		}
	}

	else if(s.type == ICE_BOLT)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if(scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->C !=NULL)
			{
				Creature *c = scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->C;
				c->CurHp =- s.Damage;
				c->status = FROZEN;
				w->AP -= s.Cost;
			}
			else if(scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->W != NULL)
			{
				Wizard *w2 = scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->W;
				w2->CurHp =- s.Damage;
				w2->status = FROZEN;
				w->AP -= s.Cost;
			}
		}
	}
}