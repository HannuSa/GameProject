#include "Input.h"

Input::Input(Scene *c,sf::RenderWindow *w)
{
	scene = c;
	window = w;
	indicator = -1;
}

Input::~Input()
{}

void Input::Update()
{
	std::vector<Wizard*>* Temp=scene->GetWizards();
	MoveMap();
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

			if(scene->Selected != NULL)
				{
					for(unsigned int s = 0; s < scene->Selected->Spells.size();s++)
					{
					if(scene->Selected->Spells[s].Selected==true)
					{
							CastSpell(scene->Selected,scene->Selected->Spells[s]);
					}
					}
				}
			if(SetDestination()==true)
			{
				if(scene->Selected->AP>0)
				{
					if(scene->Selected->GetPosition() != Destination)
					{
						if(!scene->Selected->path.empty())
						{
							scene->Selected->Move();
							scene->Selected->AP-=1;
						}
					}
				}
			}
	}

	else if(scene->GetState()->returnState() == GROUP_1_TURN && scene->CheckTurnEnd() == true)
	{
		for(int i = 0; i<Temp->size();i++)
		{
			Temp->at(i)->AP+=scene->GetWizards()->at(i)->APMax;
			Temp->at(i)->Spells[0].Selected=false;
			Temp->at(i)->moving=false;
			
		}
		std::vector<Creature*>* Temp2 = scene->GetCreatures();
		for(unsigned int i = 0; i<Temp2->size();i++)
		{
			if(scene->GetTileByPos(Temp2->at(i)->GetPosition()) ==TILE_FIRE)
			{
				if(Temp2->at(i)->GetType() != 6)
				{
				Temp2->at(i)->CurHp -= 2;
				}
			}
		}
		//scene->Selected = NULL;
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
		if(scene->DrawPos.x < 0)
		{
		scene->DrawPos.x+=15;
		}
	}
	else if(sf::Mouse::getPosition(*window).x>700)
	{
		if(scene->DrawPos.x > -2480)
		{
		scene->DrawPos.x-=15;
		}
	}
	else if(sf::Mouse::getPosition(*window).y<100)
	{
		if(scene->DrawPos.y < 0)
		{
		scene->DrawPos.y+=15;
		}
	}
	else if(sf::Mouse::getPosition(*window).y>500)
	{
		if(scene->DrawPos.y > -2688)
		{
		scene->DrawPos.y-=15;
		}
	}
}

void Input::Select()
{
	sf::Vector2i WinPos = sf::Mouse::getPosition(*window);
	sf::Vector2<float> draw = scene->DrawPos;

	WinPos.x -= draw.x;
	WinPos.y -= draw.y;

	if(scene->GetCreatureByPos(WinPos/32)->W != NULL)
	{
		if(scene->GetCreatureByPos(WinPos/32)->W->status != DEAD)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)== true)
			{
				scene->Selected = scene->GetCreatureByPos(WinPos/32)->W;
				scene->Selected->Selected = true;
			}
		}
	}
}

bool Input::SetDestination()
{
	sf::Vector2<float> draw = scene->DrawPos;
			if(scene->Selected != NULL)
			{

				if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)==true)
				{
					Destination.x = (int)((sf::Mouse::getPosition(*window).x-draw.x)/32);
					Destination.y = (int)((sf::Mouse::getPosition(*window).y-draw.y)/32);
					scene->Selected->moving=true;
					scene->Selected->SetPath(scene->FindPath(scene->Selected->GetPosition(),Destination));
					return true;
				}

				if(scene->Selected->moving==true)
				{
					return true;
				}
			}
	return false;
}

void Input::SelectSpell()
{
	if(scene->Selected != NULL)
	{
		for(unsigned int s = 0; s < scene->Selected->Spells.size();s++)
		{
			if(scene->Selected->Spells[s].type == MAGIC_MISSILE && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				if(scene->Selected->AP >= scene->Selected->Spells[s].Cost)
				{
					indicator = s;
					scene->Selected->Spells[s].Selected=true;
				}
				else 
				{
					printf("Not enough actionpoints");
				}
			}
			else if(scene->Selected->Spells[s].type == FIREBALL && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				if(scene->Selected->AP >= scene->Selected->Spells[s].Cost)
				{
					indicator = s;
					scene->Selected->Spells[s].Selected=true;
				}
				else 
				{
					printf("Not enough actionpoints");
				}
			}
			else if(scene->Selected->Spells[s].type == RAISE_UNDEAD && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				if(scene->Selected->AP >= scene->Selected->Spells[s].Cost)
				{
					indicator = s;
					scene->Selected->Spells[s].Selected=true;
				}
				else 
				{
					printf("Not enough actionpoints");
				}
			}
			//add more so no need to copy pasta that much
			else if(scene->Selected->Spells[s].type == ICE_BOLT && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
			
			}
		}
		for(int x = 0; x < scene->Selected->Spells.size();x++)
		{
			if(indicator != x)
			{
				scene->Selected->Spells[x].Selected = false;
			}
		}
	}
}

void Input::CastSpell(Wizard *w,Spell s)
{
	sf::Vector2i WinPos = sf::Mouse::getPosition(*window);
	sf::Vector2<float> draw = scene->DrawPos;

	WinPos.x -= draw.x;
	WinPos.y -= draw.y;

	if(s.type == MAGIC_MISSILE)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			scene->GetCreatureByPos(WinPos/32);

			if(scene->GetCreatureByPos(WinPos/32)->C !=NULL)
			{
				scene->GetCreatureByPos(WinPos/32)->C->CurHp -= s.Damage;
				w->AP -= s.Cost;
			}
			else if(scene->GetCreatureByPos(WinPos/32)->W != NULL)
			{
				/*sf::Mouse::getPosition(*window)/32*/
				scene->GetCreatureByPos(WinPos/32)->W->CurHp =- s.Damage;
				w->AP -= s.Cost;
			}
		}
	}

	else if(s.type == FIREBALL)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if(scene->GetCreatureByPos(WinPos/32)->C !=NULL)
			{
				Creature *c = scene->GetCreatureByPos(WinPos/32)->C;
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
			else if(scene->GetCreatureByPos(WinPos/32)->W != NULL)
			{
				Wizard *w2 = scene->GetCreatureByPos(WinPos/32)->W;
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
			if(scene->GetCreatureByPos(WinPos/32)->C !=NULL)
			{
				Creature *c = scene->GetCreatureByPos(WinPos/32)->C;
				c->CurHp =- s.Damage;
				c->status = FROZEN;
				w->AP -= s.Cost;
			}
			else if(scene->GetCreatureByPos(sf::Mouse::getPosition(*window)/32)->W != NULL)
			{
				Wizard *w2 = scene->GetCreatureByPos(WinPos/32)->W;
				w2->CurHp =- s.Damage;
				w2->status = FROZEN;
				w->AP -= s.Cost;
			}
		}
	}

		else if(s.type == STONE_WALL)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			scene->GetCreatureByPos(WinPos/32);

			if(scene->GetCreatureByPos(WinPos/32)->C ==NULL)
			{
					//create wall
					w->AP -= s.Cost;
			}
			else if(scene->GetCreatureByPos(WinPos/32)->W == NULL)
			{
					//create wall
					w->AP -= s.Cost;
			}
		}
	}

	else if(s.type == RAISE_UNDEAD)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			scene->GetCreatureByPos(WinPos/32);

			if(scene->GetCreatureByPos(WinPos/32)->C !=NULL)
			{
				if(scene->GetCreatureByPos(WinPos/32)->C->status == DEAD)
				{
					//raise undead
					w->AP -= s.Cost;
				}
			}
			else if(scene->GetCreatureByPos(WinPos/32)->W != NULL)
			{
				if(scene->GetCreatureByPos(WinPos/32)->W->status == DEAD)
				{
					//raise undead
					w->AP -= s.Cost;
				}
			}
		}
	}
		else if(s.type == SUMMON_DEMON)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			scene->GetCreatureByPos(WinPos/32);

			if(scene->GetCreatureByPos(WinPos/32)->C ==NULL)
			{
					//summon demon
					w->AP -= s.Cost;
			}
			else if(scene->GetCreatureByPos(WinPos/32)->W == NULL)
			{
					//summon demon
					w->AP -= s.Cost;
			}
		}
	}
		else if(s.type == HEAL)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			scene->GetCreatureByPos(WinPos/32);

			if(scene->GetCreatureByPos(WinPos/32)->C !=NULL)
			{
				if(scene->GetCreatureByPos(WinPos/32)->C->status == DEAD)
				{
					scene->GetCreatureByPos(WinPos/32)->C->CurHp += 5;
					w->AP -= s.Cost;
				}
			}
			else if(scene->GetCreatureByPos(WinPos/32)->W != NULL)
			{
				if(scene->GetCreatureByPos(WinPos/32)->W->status == DEAD)
				{
					scene->GetCreatureByPos(WinPos/32)->W->CurHp += 5;
					w->AP -= s.Cost;
				}
			}
		}
	}
}