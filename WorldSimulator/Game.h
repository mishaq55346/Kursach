#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include "Menu.h"
#include <thread>
#include "random"
#include "Tile.h"
#include <queue>
#include <list>

using namespace std;

class Point
{
public:
	int x = 0, y = 0;
	Point(int x, int y) : x(x), y(y){}
};

class Game
{
private:
	int x = 10;
	int y = 10;
public:

	ALLEGRO_COLOR colors[7];

	const int width = 1000;
	const int height = 600;

	
	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *logo;
	RoundButton button_main_menu;
	RoundButton button_back;


	list<vector<Tile>> previousStates;
	bool stable = false;
	bool relogic = true;
	int ext_code = -1;
	
	const int speed = 50;//in msec per frame
	vector<Tile> tiles = {};
	bool mouse_up;

	void init(int x, int y);
	static int randN();
	void draw();

	vector<Point> getPNeighbours(int x, int y);
	int getTNeighboursCount(int x, int y);
	vector<Tile> getTNeighbours(int x, int y);

	void logic(ALLEGRO_EVENT ev);

	void onClick(int x, int y, ALLEGRO_EVENT ev);
	void markKill();
	void giveBirth();
	void applyChanges();
	ALLEGRO_COLOR getDominateColor(int x, int y);

	void onExit();
};