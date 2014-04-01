#ifndef TileMap_H
#define TileMap_H

#include "Tile.h"

#define TILEMAP_WIDTH 100
#define TILEMAP_HEIGHT 100

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class TileMap
{
public:
	TileMap();
	~TileMap(void);

	TileType tiles[TILEMAP_WIDTH][TILEMAP_HEIGHT];
};
#endif

/*
	TO DO:
	id ??
	tiletype counts!!!

References:

float Point2D::GetDistance(const Point2D& other) const
{
	return std::sqrt(GetDistanceSqrd(other));
}

float Point2D::GetDistanceSqrd(const Point2D& other) const
{
	int deltaX = x - other.x;
	int deltaY = y - other.y;

	return (float)(deltaX * deltaX) + (float)(deltaY * deltaY);
}
---------------------------------------------------
	bool FindPath(Point2D start, Point2D end);

	bool PathFinder::FindPath(Point2D start, Point2D end)
{
	return FindPathReversed(end, start);
}
---------------------------------------------------
bool FindPathReversed(Point2D start, Point2D end);

bool PathFinder::FindPathReversed(Point2D start, Point2D end)
{
	clearVectors();

	SearchNode* startNode = new SearchNode(start, 
		start.y * world->GetWidth() + start.x,  NULL);

	SearchNode* goalNode = new SearchNode(end,
		end.y * world->GetWidth() + end.x, NULL);

	startNode->G = 0;
	startNode->H = startNode->HeuristicDistance(*goalNode);
	
	openList.push_back(startNode);

	while (!openList.empty())
	{
		SearchNode* currentNode = getNextNode();

		if (currentNode->id == goalNode->id)
		{
			goalNode->nextNode = currentNode->nextNode;

			for (vector<SearchNode*>::iterator iter = openList.begin();
				 iter != openList.end();
				 iter++)
			{
				world->GetTile((*iter)->position)->tileChar = 'O';
			}

			SearchNode* getPath = goalNode;
			while (getPath != NULL)
			{
				if (world->GetTile(getPath->position)->tileChar == 'O')
				{
					world->GetTile(getPath->position)->tileChar = '?';
				}
				else
				{
					world->GetTile(getPath->position)->tileChar = 'P';
				}

				pathToGoal.push_back(new Point2D(getPath->position));
				getPath = getPath->nextNode;
			}

			return true;
		}
		else
		{
			//rightCell
			pathOpened(currentNode->position + Point2D(1, 0), currentNode->G+1, currentNode, goalNode);
			//leftCell
			pathOpened(currentNode->position + Point2D(-1, 0), currentNode->G+1, currentNode, goalNode);
			//upperCell
			pathOpened(currentNode->position + Point2D(0, -1), currentNode->G+1, currentNode, goalNode);
			//LowerCell
			pathOpened(currentNode->position + Point2D(0, 1), currentNode->G+1, currentNode, goalNode);
			
			//upperRight
			pathOpened(currentNode->position + Point2D(1, -1), currentNode->G+1.414f, currentNode, goalNode);
			//uppperLeft
			pathOpened(currentNode->position + Point2D(-1, -1), currentNode->G+1.414f, currentNode, goalNode);
			//lowerRight
			pathOpened(currentNode->position + Point2D(1, 1), currentNode->G+1.414f, currentNode, goalNode);
			//LowerLeft
			pathOpened(currentNode->position + Point2D(-1, 1), currentNode->G+1.414f, currentNode, goalNode);
			
		}
	}

	return false;
}
---------------------------------------------------
void PathFinder::clearVectors()
{	
	for (unsigned int i = 0; i < openList.size(); i++)
	{
		delete openList[i];
		openList[i] = NULL;
	}
	openList.clear();
	
	for (unsigned int i = 0; i < closedList.size(); i++)
	{
		delete closedList[i];
		closedList[i] = NULL;
	}
	closedList.clear();

	for (unsigned int i = 0; i <pathToGoal.size(); i++)
	{
		delete pathToGoal[i];
		pathToGoal[i] = NULL;
	}
	pathToGoal.clear();
}

---------------------------------------------------

SearchNode* getNextNode();

SearchNode* PathFinder::getNextNode()
{
	float bestF = FLT_MAX;
	int cellIndex = -1;

	SearchNode* nextNode = NULL;

	for (unsigned int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->GetF() <= bestF)
		{
			bestF = openList[i]->GetF();
			cellIndex = i;
		}
	}

	if (cellIndex != -1)
	{
		nextNode = openList[cellIndex];
		
		for (int i = 0; i < closedList.size(); i++)
		{
			if (closedList[i]->id == nextNode->id)
			{
				break;
			}
		}
		closedList.push_back(nextNode);
		world->GetTile(nextNode->position)->tileChar = 'C';
		openList.erase(openList.begin() + cellIndex);

		return nextNode;
	}
	else
		return NULL;
}

---------------------------------------------------

void PathFinder::pathOpened(Point2D position, float newCost, SearchNode* nextNode, SearchNode* goalNode)
{
	//tähän väliin checkki että voidaanko mennä ja return jos on
	if (position.x < 0 || position.x > world->GetWidth() ||
		position.y < 0 || position.y > world->GetHeight() ||
		!world->GetTile(position)->walkable)
		return;

	int id = position.y * world->GetWidth() + position.x;

	
	for (unsigned int i = 0; i < closedList.size(); i++)
	{
		if (id == closedList[i]->id)
			return;
	}
	
	SearchNode* newNode = new SearchNode(position, id, nextNode);
	newNode->G = newCost;
	newNode->H = newNode->HeuristicDistance(*goalNode);
	
	for (unsigned int i = 0; i < openList.size(); i++)
	{
		if (id == openList[i]->id)
		{
			if (newNode->G < openList[i]->G)
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

---------------------------------------------------

std::vector<SearchNode*> openList;
	std::vector<SearchNode*> closedList;
	std::vector<Point2D*> pathToGoal;

	Point2D PathFinder::GetNextPathPosition()
{
	Point2D nextPos(*pathToGoal.back());

	delete (pathToGoal.back());
	pathToGoal.pop_back();

	return nextPos;
}
	
	Own shit:


	Node SearchNode::FindNextStep(int Sx,int Sy,int Ex,int Ey)
{
	Node start;
	start.x = Sx;
	start.y = Sy;
	start.DistanceStart = 0;

	float dx = Sx-Ex;
	float dy = Sy-Ey;

	start.EstimateDistance= start.DistanceStart+std::sqrt((dx*dx)+(dy*dy));
	start.previousNode=NULL;

	OpenList.push_back(start);

	while(!OpenList.empty() ||&& FindBest()->x!=Ex && FindBest()->y!=Ey||)
	{
		Node Current = *FindBest();
		if(Current.x==Ex&&Current.y == Ey)
		{
			//return reconstruct path???
		}

		ClosedList.push_back(Current);

		
		for(int i = 0; i<ClosedList.size(); i++)
		{
			if(Current.x-1<=ClosedList[i].x<=Current.x+1)
			{
				if(Current.y-1<=ClosedList[i].y<=Current.y+1)
				{	

				}
			}
		}
	}

	
Node* SearchNode::FindBest()
{
	Node* Result;
	int BestIndex;
	Result->EstimateDistance= 1000000;
	for (int i = 0; i < OpenList.size(); i++)
	{
		if (OpenList[i].EstimateDistance<Result->EstimateDistance)
		{
			Result = &OpenList[i];
			BestIndex = i;
		}
	}
	OpenList.erase(OpenList.begin()+BestIndex);

	return Result;
}
}










*/