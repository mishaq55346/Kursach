#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <Windows.h>
#include "RoundButton.h"
#include "Panel.h"

using namespace std;

class Menu
{
	
public:

	
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;

	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout;

	ALLEGRO_BITMAP *image;
	RoundButton *button_continue;
	RoundButton *button_back;
	Panel*panel_x;
	Panel*panel_y;
	int width = 1000;
	int height = 600;
	bool get_event;
	int ext_code = -1;
	bool mouse_up = true;
	int x = 20;
	int y = 20;

	void init();
	void draw();
	void logic();

	void onExit();

	void onClick(int x, int y);
};

