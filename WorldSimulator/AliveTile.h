#pragma once
#include <allegro5/allegro5.h>
#include <iostream>


class Tile
{
public:
	enum AliveTileState {T_Dyeing, T_Born, T_Live};
	AliveTileState State = T_Live;

	int x = 0, y = 0;
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
	Tile()
	{
		//color = al_map_rgb()
	}
	Tile(int x, int y) : x(x), y(y)
	{
		//color = al_map_rgb()
	}
	void print()
	{
		std::cout << "Tile at " << x << "-" << y << ". Current state is " << State << endl;
	}
	bool operator==(Tile tile)
	{
		return (x == tile.x && y == tile.y);
	}
};
