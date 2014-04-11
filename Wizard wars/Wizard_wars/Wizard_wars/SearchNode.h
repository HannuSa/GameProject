#ifndef SEARCHNODE_H
#define SEARCHNODE_H

#include "Tile.h"
#include <SFML\System\Vector2.hpp>
#include <math.h>

struct SearchNode
{
	SearchNode* nextNode;

	sf::Vector2<int> Position;

	float G, H , T;

	SearchNode() : nextNode(0)
	{	}

	SearchNode(sf::Vector2<int> Pos,TileType t, SearchNode* Next = 0) : Position(Pos), nextNode(Next), G(0), H(0)
	{
		switch(t)
		{
		TILE_GRASS:
			T = 1.0;
			break;
		TILE_ROCK:
			T = 3.0;
			break;
		TILE_FLOOR:
			T = 1.0;
			break;
		TILE_FIRE:
			T = 2.0;
			break;
		default:
			T = 0.0;
			break;
		}
	}

	float GetF()
	{
		return G + H;
	}

	float HeuristicDistance(SearchNode &otherNode)
	{
		//return 0; <--- ???
		int x = abs(Position.x - otherNode.Position.x);
		int y = abs(Position.y - otherNode.Position.y);

		//return (float)x+y; //manhattan
		return (float)x+y + (1.414f - 2) * std::min(x,y); //diagonal
	}
};

#endif