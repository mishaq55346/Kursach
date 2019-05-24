#pragma once
#include <allegro5/allegro5.h>
#include <iostream>
#include <random>


class Tile
{
public:
	int x = 0, y = 0;
	ALLEGRO_COLOR color = al_map_rgb(0, 0, 125);

	enum TileState { T_Dyeing, T_Born, T_Live };
	TileState State = T_Live;

	Tile(){}
	Tile(int x, int y) : x(x), y(y)
	{
	}
	Tile(int x, int y, TileState state) : x(x), y(y), State(state)
	{
	}
	Tile(int x, int y, ALLEGRO_COLOR color) : x(x), y(y), color(color)
	{
		this->color = color;
	}
	Tile(int x, int y, TileState state, ALLEGRO_COLOR color) : x(x), y(y), State(state), color(color){}
	
	void print() const
	{
		std::cout << "Tile at " << x << "-" << y << ". Current state is ";
		switch (State)
		{
		case T_Live:
			std::cout << "live, ";
			break;
		case T_Born:
			std::cout << "just born, ";
			break;
		case T_Dyeing:
			std::cout << "dyeing, ";
			break;
		}
		std::cout << "color is " << color.r * 255 << " " << color.g * 255 << " " << color.b * 255 << std::endl;
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
