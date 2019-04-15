#pragma once

#include <Windows.h>
#include "Menu.h"
#include <string>
//#include <random>
#include "random"

using namespace std;


class Start
{
public:
	ALLEGRO_EVENT_QUEUE *disp_queue;
	ALLEGRO_EVENT_QUEUE *mouse_queue;
	ALLEGRO_EVENT event_disp;
	ALLEGRO_EVENT event_mouse;
	ALLEGRO_TIMEOUT timeout;
	int ext_code = -1;
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_BITMAP *image = nullptr;

	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_DISPLAY_MODE disp_mode;
	ALLEGRO_FONT *font24;

	RoundButton *button_start;

	bool mouse_up = true;
	const float FPS = 60.0;
	int screen_centreX;
	int screen_centreY;
	int width;
	int height;
	int b_corr;

	void init();
	void draw();
	void logic();
	void onClick(int x, int y);
	void onExit();
};

