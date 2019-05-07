#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "Menu.h"
#include <thread>
#include "random"
#include "Tile.h"

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
	
	const int width = 1000;
	const int height = 600;

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *logo;
	RoundButton button_main_menu;
	RoundButton button_back;

	float FPS = 5.0;
	bool redraw = true;
	int ext_code = -1;
	
	const int speed = 100;//in msec per frame
	vector<Tile> tiles = {};
	bool mouse_up;

	void init(int x, int y);
	static int randN();
	void draw();

	vector<Point> getPNeighbours(int x, int y);
	int getTNeighboursCount(int x, int y);
	vector<Tile> getTNeighbours(int x, int y);

	void logic(ALLEGRO_EVENT ev);
	void findAnomalies();

	void onClick(int x, int y, ALLEGRO_EVENT ev);
	void markKill();
	void giveBirth();
	void applyChanges();
	ALLEGRO_COLOR getDominateColor(int x, int y);


	void print(vector<Point> points)
	{
		for (auto p : points)
			cout << p.x << "---" << p.y << endl;
		cout << "---------------\n";
	}
	void print(vector<Tile> tiles)
	{
		cout << "---------------\n";
		for (auto t : tiles)
			t.print();
		cout << "======\n";
	}

	void onExit();
};