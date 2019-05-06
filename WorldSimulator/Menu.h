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

	ALLEGRO_BITMAP *image;
	RoundButton *button_continue;
	RoundButton *button_back;
	Panel*panel_x;
	Panel*panel_y;
	int width = 1000;
	int height = 600;
	int ext_code = -1;
	bool mouse_up = true;
	int x = 20;
	int y = 20;

	void init();
	void draw();
	void logic(ALLEGRO_EVENT ev);

	void onExit();
	void onClick(int x, int y, ALLEGRO_EVENT ev);

	
};

