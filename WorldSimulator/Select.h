#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <iostream>
#include <Windows.h>
#include "RoundButton.h"
#include <string>
#include "random"
#include "Panel.h"
#include "Tile.h"

using namespace std;

class Select
{
public:
	int x = 10;
	int y = 10;
	vector<Tile> tiles;

	ALLEGRO_BITMAP *image;

	ALLEGRO_SAMPLE *audio_single = NULL;
	RoundButton *button_continue;
	RoundButton *button_back;
	Panel *panel_x;
	Panel *panel_y;
	const int speed = 50;//in msec per frame

	int scale = 20;

	bool mouse_up = true;

	int ext_code = -1;

	const int width = 1000;
	const int height = 600;

	void init(int x, int y);
	void draw();
	void logic(ALLEGRO_EVENT ev);
	void onClick(int x, int y, ALLEGRO_EVENT ev);
	void onExit();
};