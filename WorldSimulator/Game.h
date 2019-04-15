#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "Menu.h"
#include <thread>
#include "random"

using namespace std;

class Game
{
private:
	int x = 10;
	int y = 10;
public:
	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	float FPS = 20.0;
	bool redraw = true;
	int ext_code = -1;
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_DISPLAY_MODE disp_mode;
	ALLEGRO_BITMAP *image;
	const int speed = 100;//in msec per frame
	int **map = new int*[0];
	bool mouse_up;

	

	RoundButton button_main_menu;
	RoundButton button_back;

	int screen_centreX;
	int screen_centreY;
	const int width = 1000;
	const int height = 600;

	void init(int x, int y);
	int randN(int min, int max);
	void draw();

	int nCount(int i, int j);

	void logic();
	
	void onClick(int x, int y);
	void markKill();
	void giveBirth();
	void applyChanges() const;

	void onExit();
};
