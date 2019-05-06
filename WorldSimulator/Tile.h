#pragma once
#include <allegro5/allegro5.h>
#include <iostream>
#include <random>


class Tile
{
public:
	int x = 0, y = 0;
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

	enum TileState { T_Dyeing, T_Born, T_Live };
	TileState State = T_Live;

	Tile(){}
	Tile(int x, int y) : x(x), y(y)
	{
		color = al_map_rgb(randN(), randN(), randN());
	}
	Tile(int x, int y, TileState state) : x(x), y(y), State(state)
	{
		color = al_map_rgb(randN(), randN(), randN());
	}
	Tile(int x, int y, ALLEGRO_COLOR color) : x(x), y(y), color(color){}
	Tile(int x, int y, TileState state, ALLEGRO_COLOR color) : x(x), y(y), State(state), color(color){}
	
	void print() const
	{
		std::cout << "Tile at " << x << "-" << y << ". Current state is ";
		switch (State)
		{
		case T_Live:
			std::cout << "live" << std::endl;
			break;
		case T_Born:
			std::cout << "just born" << std::endl;
			break;
		case T_Dyeing:
			std::cout << "dyeing" << std::endl;
			break;
		}
	}
	bool operator==(Tile tile) const
	{  
		return (x == tile.x && y == tile.y && tile.State == State);
	}
	int randN()
	{
		std::random_device rd;
		std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 
		return mersenne();
	}
};
