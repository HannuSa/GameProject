#include "Render.h"


Render::Render(Scene *scene)
	:scene(scene)
{}


Render::~Render(void)
{
}


void Render::update()
{
	/*
	scene->getTilemap()->tiles;

	--> render tiles
	*/

	for(int x = 0; x < TILEMAP_WIDTH; ++x)
	{
		for(int y = 0; y < TILEMAP_HEIGHT; ++y)
		{

			//draw ( x * TILE_WIDTH, y * TILE_HEIGHT );


			//OR COLLISION CHECK

			// rect x,y same as draw     + TILE_WIDHT, TILE_HEIGHT

		}
	}
}