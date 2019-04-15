#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <Windows.h>
#include "RoundButton.h"
#include <string>
//#include <random>
#include "random"
#include "Panel.h"

using namespace std;

class Select
{
public:
	int x = 10;
	int y = 10;
	ALLEGRO_EVENT_QUEUE *disp_queue;
	ALLEGRO_EVENT_QUEUE *mouse_queue;
	ALLEGRO_EVENT event_disp;
	ALLEGRO_EVENT event_mouse;
	ALLEGRO_TIMEOUT timeout;
	int ext_code = -1;
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_DISPLAY_MODE disp_mode;

	ALLEGRO_BITMAP *image;

	RoundButton *button_continue;
	RoundButton *button_back;
	Panel *panel_x;
	Panel *panel_y;
	const int speed = 50;//in msec per frame
	int **map = new int*[0];
	//shared_ptr<int*> p1_ptr(Select::map);

	int scale = 20;

	bool mouse_up = true;

	int screen_centreX;
	int screen_centreY;
	const int width = 1000;
	const int height = 600;
	int b_corr;

	void init(int x, int y);
	void draw();
	void logic();
	void onClick(int x, int y);

	void onExit();
};
