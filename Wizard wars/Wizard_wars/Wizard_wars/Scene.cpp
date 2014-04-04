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
}


Scene::~Scene(void)
{
	delete CurrentState;
}

void Scene::AddCreature(Creature *c)
{
	 Creatures.push_back(c);

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
	}

	if(CurrentState->returnState() == GROUP_2_TURN && CheckTurnEnd() == false)
	{
		Creatures[0]->acting=true;
		for(int i = 0; i < Creatures.size(); i++)
		{
			if(Creatures[i]->status!=DEAD)
			{
				if(Creatures[i]->acting==true)
				{

					if(Creatures[i]->GetType()==2)
					{
						if(Creatures[i]->AP>0)
						{
							if(GetDistance(GetTargetPos(),Creatures[i]->GetPosition())>1)
							{
								MoveCreature(i);
								Creatures[i]->AP-=1;
							}
							else
							{
								Attack(Creatures[i],Wizards[0]);
								Creatures[i]->AP-=1;
							}
						}
						else
						{
							Creatures[i]->acting=false;
							Creatures[i+1]->acting=true;
						}
					}
				}
			}
			else
			{
				Creatures[i]->acting=false;
				Creatures[i+1]->acting = true;
			}
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
				}
			}
			CurrentState->NewState(GROUP_1_TURN);
		}
}

void Scene::MoveCreature(int T)
{
	Creatures[T]->Move(FindPath(Creatures[T]->GetPosition(),GetTargetPos()));
}

TileType Scene::GetTileByPos(sf::Vector2<int> Pos)
{
	return tilemap.tiles[Pos.x][Pos.y];
}


sf::Vector2<int> Scene::GetTargetPos()
{
	sf::Vector2<int> FinalPos(Wizards.at(0)->GetPosition());
	return FinalPos;
}

double Scene::GetDistance(sf::Vector2<int> Target, sf::Vector2<int> Begin)
{
	double result = std::sqrt(((float)Target.x-Begin.x)*(Target.x-Begin.x)+(Target.y-Begin.y)*(Target.y-Begin.y));
	return result;
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
		for(int i = 0; i < Creatures.size(); i++)
		{
			if (Creatures[i]->AP > 0)
			{
				return TurnEnd;
			}
		}
	}
	 TurnEnd=true;
	 return TurnEnd;
}

Target* Scene::GetCreatureByPos(sf::Vector2<int> P)
{
	std::cout<<"X:" <<P.x<<"Y:"<<P.y<<std::endl;
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


sf::Vector2<int> Scene::FindPath(sf::Vector2<int> Start,sf::Vector2<int> End)
{
#define NODATA -1
#define BLOCK -2

	sf::Vector2<int> positionPatch;
	positionPatch.x = 0;
	positionPatch.y = 0;

int fillData[TILEMAP_WIDTH][TILEMAP_HEIGHT];

//init the array
for(int x = 0;x < TILEMAP_WIDTH;x++)
{
	for(int y = 0; y < TILEMAP_HEIGHT;y++)
	{
		fillData[x][y] = NODATA;
		sf::Vector2<int> tempPos;

		tempPos.x = x;
		tempPos.y = y;

		if(GetTileByPos(tempPos)==TILE_ROCK)
		fillData[x][y] = BLOCK;

		for(int i=0;i<Creatures.size();i++)
		{
			if(Creatures[i]->GetPosition()==tempPos)
			{
			fillData[x][y] = BLOCK;
			}
		}
	}
}

fillData[Start.x][Start.y] = 0;

//start filling the array
#define PATH_FILL_POS(p_x,p_y) if(fillData[x + p_x][y + p_y] == NODATA){fillData[x + p_x][y + p_y] = (i+1);}

//Fill

for(int i = 0;i < 100;i++)
{
	for(int x = 0;x < TILEMAP_WIDTH;x++)
	{
		for(int y = 0; y < TILEMAP_HEIGHT;y++)
		{
			if(fillData[x][y] == i)
			{
				//Found tile that represents our current depth in the search!

				//Fill the tiles near it
				PATH_FILL_POS(0,1);
				PATH_FILL_POS(0,-1);
				PATH_FILL_POS(1,0);
				PATH_FILL_POS(-1,0);

				PATH_FILL_POS(1,1);
				PATH_FILL_POS(-1,-1);
				PATH_FILL_POS(1,-1);
				PATH_FILL_POS(-1,1);

				if(x == End.x && y == End.y)
				{
				break;
				}
			}
		}
	}
}

//TODO: bailout when search not possible

//Walk back from the target and find the fastest route
    sf::Vector2<int> pos;
	pos = End;

int i = fillData[pos.x][pos.y];// + 1 because we do i-- in the start
while(i > 0)
{
	if(i == 1)
	{
	//we found the next step!
	return pos;
	}

//Find the next value near us

//HACK: This isn't pretty, but it works :D

	if(fillData[pos.x+1][pos.y] == (i - 1))
	{
		pos.x++;
		i--;
		continue;
	}
	if(fillData[pos.x-1][pos.y] == (i - 1))
	{
		pos.x--;
		i--;
		continue;
	}
	if(fillData[pos.x][pos.y+1] == (i - 1))
	{
		pos.y++;
		i--;
		continue;
	}
	if(fillData[pos.x][pos.y-1] == (i - 1))
	{
		pos.y--;
		i--;
		continue;
	}

	if(fillData[pos.x+1][pos.y+1] == (i - 1))
	{
		pos.x++;
		pos.y++;
		i--;
	continue;
	}
	if(fillData[pos.x-1][pos.y-1] == (i - 1))
	{
		pos.x--;
		pos.y--;
		i--;
	continue;
	}
	if(fillData[pos.x-1][pos.y+1] == (i - 1))
	{
		pos.x--;
		pos.y++;
		i--;
	continue;
	}
	if(fillData[pos.x+1][pos.y-1] == (i - 1))
	{
		pos.y--;
		pos.x++;
		i--;
	continue;
	}
}

pos = Start;//Could not calculate the path!
return pos;
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


	//Not sure about this
	/*for (unsigned int i = 0; i <pathToGoal.size(); i++)
	{
		delete pathToGoal[i];
	}
	pathToGoal.clear();*/
}

bool Scene::OwnFindPath(sf::Vector2<int> Start,sf::Vector2<int> End)
{
	return FindPathReversed(Start,End);
}

bool Scene::FindPathReversed(sf::Vector2<int> Start,sf::Vector2<int> End)
{
	clearVectors();

	SearchNode* startNode = new SearchNode(Start,NULL);

	SearchNode* goalNode = new SearchNode(End, NULL);

	startNode->G = 0;
	startNode->H = startNode->HeuristicDistance(*goalNode);

	openList.push_back(startNode);

	while(!openList.empty())
	{
		SearchNode* currentNode = getNextNode();

		if(currentNode->Position == goalNode->Position)
		{
		
		
		}
	}

}