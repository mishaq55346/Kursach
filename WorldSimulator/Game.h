#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "Menu.h"
#include <thread>
#include "random"
#include "AliveTile.h"

using namespace std;

class Point
{
public:
	int x = 0, y = 0;

};

class Game
{
private:
	int x = 10;
	int y = 10;
public:
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_DISPLAY_MODE disp_mode;
	int screen_centreX;
	int screen_centreY;
	const int width = 1000;
	const int height = 600;

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *logo;
	RoundButton button_main_menu;
	RoundButton button_back;

	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	float FPS = 5.0;
	bool redraw = true;
	int ext_code = -1;
	
	const int speed = 100;//in msec per frame
	int **map = new int*[0];
	vector<AliveTile> tiles = {};
	bool mouse_up;

	void init(int x, int y);
	static int randN();
	void draw();

	int nCount(int i, int j);
	int Count(AliveTile tile);
	vector<Point> getNeighbours(int x, int y);
	vector<Point> getNeighbours(AliveTile tile);
	int Count(int x, int y);

	void logic();
	
	void onClick(int x, int y);
	void markKill();
	void giveBirth();
	void applyChanges() const;

	void onExit();
};