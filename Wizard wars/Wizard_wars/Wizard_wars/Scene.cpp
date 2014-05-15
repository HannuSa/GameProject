#include "Scene.h"
#include <cmath>
#include <iostream>

Scene::Scene()
{}

Scene::Scene(Wizard *w)
{
	Wizards.push_back(w);
	CurrentState = new GameState();
	DrawPos = sf::Vector2<float>(0,0);
	CurrentState->NewState(GROUP_1_TURN);
	Selected = NULL;
}


Scene::~Scene(void)
{
	delete CurrentState;
}

void Scene::AddCreature(Creature *c)
{
	 Creatures.push_back(c);
	 Indicator = Creatures.begin();
}

void Scene::AddWizard(Wizard *w)
{
	Wizards.push_back(w);
}

void Scene::AddObject(GameObject *g)
{
	Objects.push_back(g);
}

GameState* Scene::GetState()
{
	return CurrentState;
}


void Scene::update()
{
	for(int i = 0; i < Wizards.size(); i++)
	{
		if(Wizards[i]->CurHp<=0)
		{
			Wizards[i]->status=DEAD;
			Wizards[i]->AP=0;
		}
	}
	for(int i = 0; i < Creatures.size(); i++)
	{
	if(Creatures[i]->CurHp<=0)
				{
					Creatures[i]->status=DEAD;
					Creatures[i]->AP=0;
				}
	 if(Creatures[i]->status == DESTROYED)
				{
					Creatures[i]->~Creature();
					Creatures.erase(Creatures.begin()+i);
				}
	}

	if(CurrentState->returnState() == GROUP_2_TURN && CheckTurnEnd() == false)
	{
		(*Indicator)->acting=true;

			if((*Indicator)->status!=DEAD)
			{
				if((*Indicator)->acting==true)
				{
						if((*Indicator)->AP>0)
						{
							if(GetDistance(GetTarget((*Indicator)),(*Indicator)->GetPosition())!=1)
							{
								if((*Indicator)->path.empty())
								{
									(*Indicator)->SetPath(FindPath((*Indicator)->GetPosition(),GetTarget((*Indicator))));
								}
								else
								{
								MoveCreature((*Indicator));
								(*Indicator)->AP-=1;
								}
							}
							else
							{
								Attack((*Indicator),GetCreatureByPos(GetTarget((*Indicator)))->W);
								(*Indicator)->AP-=1;
							}
						}
						else
						{
							(*Indicator)->acting=false;
							Indicator++;
						}
				}
			}
			else
			{
				(*Indicator)->acting=false;
				Indicator++;
			}
		
	}
	else if(CurrentState->returnState() == GROUP_2_TURN && CheckTurnEnd() == true)
		{
			for(int i = 0; i<Creatures.size();i++)
			{
				if(Creatures[i]->status != DEAD)
				{
				Creatures[i]->AP+=Creatures[i]->APMax;
				Creatures[i]->acting=false;
				Creatures[i]->path.clear();
				}
			}
			Indicator = Creatures.begin();
			CurrentState->NewState(GROUP_1_TURN);
		}
}

sf::Vector2<int> Scene::GetTarget(Creature *c)
{
	Wizard* t = Wizards[0];
		for(unsigned int i = 0; i < Wizards.size(); i++)
		{
				if(c->type == CHAOS_SPAWN)
				{
				if(Wizards[i]->C == SUMMONER)
					{
						return Wizards[i]->GetPosition();
					}
				}
				Wizards[i]->update();
				if(Wizards[i]->threat > t->threat)
				{
					t = Wizards[i];
				}
		}
	return t->GetPosition();
}

void Scene::MoveCreature(Creature *c)
{
	c->Move();
}

TileType Scene::GetTileByPos(sf::Vector2<int> Pos)
{
	return tilemap.tiles[Pos.x][Pos.y];
}

double Scene::GetDistance(sf::Vector2<int> Target, sf::Vector2<int> Begin)
{
	/*double result = std::sqrt(((float)Target.x-Begin.x)*(Target.x-Begin.x)+(Target.y-Begin.y)*(Target.y-Begin.y));
	return result;*/
	if(Target.x-1 == Begin.x || Target.x+1 == Begin.x || Target.x == Begin.x)
	{
		if(Target.y-1 == Begin.y || Target.y+1 == Begin.y || Target.x == Begin.x)
		{
			return 1.0;
		}
	}

	return 2.0;
}

void Scene::Attack(Creature* Attacker, Wizard* Target)
{
	Target->CurHp-=Attacker->CurDam;
}

bool Scene::CheckTurnEnd()
{
	bool TurnEnd = false;
	if(CurrentState->returnState() == GROUP_1_TURN)
	{
		for(int i = 0; i < Wizards.size(); i++)
			{
				if (Wizards[i]->AP > 0)
				{
					return TurnEnd;
				}
			}
	}

	else if(CurrentState->returnState() == GROUP_2_TURN)
	{
		if(Indicator != Creatures.end())
		{
			return TurnEnd;
		}
	}
	 TurnEnd=true;
	 return TurnEnd;
}

Target* Scene::GetCreatureByPos(sf::Vector2<int> P)
{
	//std::cout<<"X:" <<P.x<<"Y:"<<P.y<<std::endl;
	Target t;
	t.C = NULL;
	t.W = NULL;

	for(int i = 0; i<Creatures.size();i++)
	{
		if(Creatures[i]->GetPosition() == P)
		{
			t.C = Creatures[i];
		}
	}

	for(int i = 0; i<Wizards.size(); i++)
	{
		if(Wizards[i]->GetPosition() == P)
		{
			t.W = Wizards[i];
		}
	}
	return &t;
}

void Scene::clearVectors()
{
	for (unsigned int i = 0; i < openList.size(); i++)
	{
		delete openList[i];
	}
	openList.clear();
	
	for (unsigned int i = 0; i < closedList.size(); i++)
	{
		delete closedList[i];
	}
	closedList.clear();

	
	PathToGoal.clear();
}

std::vector<sf::Vector2<int>> Scene::FindPath(sf::Vector2<int> Start,sf::Vector2<int> End)
{
	return FindPathReversed(Start,End);
}

std::vector<sf::Vector2<int>> Scene::FindPathReversed(sf::Vector2<int> Start,sf::Vector2<int> End)
{
	clearVectors();

	SearchNode* startNode = new SearchNode(Start,GetTileByPos(Start),NULL);

	SearchNode* goalNode = new SearchNode(End,GetTileByPos(End), NULL);

	startNode->G = 0;
	startNode->H = startNode->HeuristicDistance(*goalNode);

	openList.push_back(startNode);

	while(!openList.empty())
	{
		SearchNode* currentNode = getNextNode();

		if(currentNode->Position == goalNode->Position)
		{
			goalNode->nextNode = currentNode->nextNode;

			for(std::vector<SearchNode*>::iterator it = openList.begin(); it != openList.end(); it++)
			{
				//propably unnecessary(honestly no fucking idea)
			}

			SearchNode* getPath = goalNode;
			while (getPath != NULL)
			{
				/*if (GetTileByPos(getPath->position) != walkable)
				{
					//error message
				}*/
				PathToGoal.push_back(getPath->Position);
				getPath = getPath->nextNode;
			}
			
			return PathToGoal;
		}
		else
		{
			//rightCell
			pathOpened(currentNode->Position + sf::Vector2<int>(1,0),currentNode->G+1,currentNode,goalNode);
			//leftCell
			pathOpened(currentNode->Position + sf::Vector2<int>(-1,0),currentNode->G+1,currentNode,goalNode);
			//upperCell
			pathOpened(currentNode->Position + sf::Vector2<int>(0,-1),currentNode->G+1,currentNode,goalNode);
			//lowerCell
			pathOpened(currentNode->Position + sf::Vector2<int>(0,1),currentNode->G+1,currentNode,goalNode);

			//upperRight
			pathOpened(currentNode->Position + sf::Vector2<int>(1,-1),currentNode->G+1.141f,currentNode,goalNode);
			//upperLeft
			pathOpened(currentNode->Position + sf::Vector2<int>(-1,-1),currentNode->G+1.141f,currentNode,goalNode);
			//lowerRight
			pathOpened(currentNode->Position + sf::Vector2<int>(1,1),currentNode->G+1.141f,currentNode,goalNode);
			//loverLeft
			pathOpened(currentNode->Position + sf::Vector2<int>(-1,1),currentNode->G+1.141f,currentNode,goalNode);
		}
	}
	PathToGoal.push_back(Start);
	return PathToGoal;
}

SearchNode* Scene::getNextNode()
{
	float bestF = FLT_MAX;
	int cellIndex = -1;

	SearchNode* nextNode = NULL;

	for(unsigned int i = 0; i<openList.size(); i++)
	{
		if(openList[i]->GetF() <= bestF)
		{
			bestF = openList[i]->GetF();
			cellIndex = i;
		}
	}

	if(cellIndex != -1)
	{
		nextNode = openList[cellIndex];

		for(int i = 0; i<closedList.size(); i++)
		{
			if(closedList[i]->Position == nextNode->Position)
			{
				break;
			}
		}
		closedList.push_back(nextNode);
		//move
		openList.erase(openList.begin()+cellIndex);

		return nextNode;
	}
	else
	{
		return NULL;
	}
}

void Scene::pathOpened(sf::Vector2<int> Position, float newCost,SearchNode* nextNode, SearchNode* goalNode)
{
	//tähän väliin checkki että voidaanko mennä ja return(eli break) jos on
	if(Position.x < 0 || Position.x > TILEMAP_WIDTH ||
		Position.y < 0 || Position.y > TILEMAP_HEIGHT ||
		GetTileByPos(Position) == TILE_WALL)
	return;
	//Checkki otusten paikoille
	for(unsigned int i = 0; i < Creatures.size(); i++)
	{
		if(Creatures[i]->GetPosition() != goalNode->Position)
		{
			if(Creatures[i]->GetPosition() == Position)
			{
				return;
			}
		}
	}
	//Checkki velhoje paikoille
	for(unsigned int j = 0; j < Wizards.size(); j++)
	{
		if(Wizards[j]->GetPosition() != goalNode->Position)
		{
			if(Wizards[j]->GetPosition() == Position)
			{
				return;
			}
		}
	}

	for(unsigned int i = 0; i < closedList.size(); i++)
	{
		if(Position == closedList[i]->Position)
		return;
	}

	SearchNode* newNode = new SearchNode(Position,GetTileByPos(Position),nextNode);
	newNode->G = newCost;
	newNode->H = newNode->HeuristicDistance(*goalNode);

	for(unsigned int i = 0; i <openList.size(); i++)
	{
		if(Position == openList[i]->Position)
		{
			if(newNode->G < openList[i]->G)
			{
				delete openList[i];
				openList.erase(openList.begin()+i);
			}
			else
			{
				delete newNode;
				return;
			}
		}
	}
	openList.push_back(newNode);
}