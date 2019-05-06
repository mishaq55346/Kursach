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
	
	int ext_code = -1;
	ALLEGRO_BITMAP *image = nullptr;

	ALLEGRO_FONT *font24;

	RoundButton *button_start;

	bool mouse_up = true;
	const float FPS = 60.0;
	int width = 1000;//
	int height = 600;//
	int b_corr;

	void init();
	void draw();
	void logic(ALLEGRO_EVENT ev);
	void onClick(int x, int y);
	void onExit();
};

