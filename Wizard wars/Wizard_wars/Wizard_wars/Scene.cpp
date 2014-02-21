#include "Scene.h"

Scene::Scene()
{}

Scene::Scene(Creature *c)
{
	Group1.push_back(c);
	CurrentState = new GameState();
}


Scene::~Scene(void)
{
	delete CurrentState;
}

void Scene::AddCreature(Creature *c)
{
	if(c->GetType()==1)
	{
	 Group1.push_back(c);
	}
	else
	{
		Group2.push_back(c);
	}
}

void Scene::update()
{
	if(CurrentState->returnState() == GROUP_1_TURN)
	{
	}
	else if(CurrentState->returnState() == GROUP_2_TURN)
	{
		MoveCreature();
	}
}

void Scene::MoveCreature()
{
	Group2[0]->Move(FindPath(Group1[0]->GetPosition(),Group1[0]->GetPosition()));
}

TileType Scene::GetTileByPos(sf::Vector2<int> Pos)
{
	return tilemap.tiles[Pos.x][Pos.y];
}

sf::Vector2<int> Scene::FindPath(sf::Vector2<int> Start,sf::Vector2<int> End)
{
#define NODATA -1
#define BLOCK -2
	End.x += 1;

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

		for(int i=0;i<Group1.size();i++)
		{
			if(Group1[i]->GetPosition()==tempPos)
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