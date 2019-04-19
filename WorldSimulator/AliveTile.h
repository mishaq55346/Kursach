#pragma once
#include <allegro5/allegro5.h>

class AliveTile
{
public:
	enum AliveTileState {T_Dyeing, T_Born, T_Live};
	AliveTileState State = T_Live;

	int x = 0, y = 0;
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
	AliveTile()
	{
		//color = al_map_rgb()
	}
	AliveTile(int x, int y) : x(x), y(y)
	{
		//color = al_map_rgb()
	}
};
