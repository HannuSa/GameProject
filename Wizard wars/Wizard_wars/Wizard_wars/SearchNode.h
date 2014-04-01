#ifndef SEARCHNODE_H
#define SEARCHNODE_H

#include "Tile.h"
#include <SFML\System\Vector2.hpp>
#include <math.h>

struct Searchnode
{
	SearchNode* nextNode;

	sf::Vector2<int> Position;

	float G, H;

	SearchNode() : nextNode(0)
	{	}

	SearchNode(sf::Vector2<int> Pos, SearchNode* Next = 0) : Position(Pos), nextNode(Next), G(0), H(0)
	{	}

	float GetF()
	{
		return G + H;
	}

	float HeuristicDistance(SearchNode& othernode)
	{
		//return 0; <--- ???

		int x = abs(Position.x - otherNode.Position.x);
		int y = abs(Position.y - otherNode.Position.y);

		//return (float)x+y; //manhattan
		return (float)x+y + (1.414f - 2) * std::min(x,y); //diagonal
	}
};

#endif