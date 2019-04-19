#pragma once
#include <allegro5/allegro5.h>

class AliveTile
{
public:
	int x, y;
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
};
