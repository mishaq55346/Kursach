#pragma once
#include "Button.h"
#include "Menu.h"
#include <string>

using namespace std;

class Panel
{

	int x1, y1, x2, y2;

public:

	
	ALLEGRO_FONT *font18;
	Panel(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2)
	{
		font18 = al_load_font("arial.ttf", 18, 0);
	};
	void draw(string text)
	{
		if (!font18) {
			cout << "font18 not loaded\n";
			exit(2);
		}
		char str[100];
		strcpy_s(str,  text.c_str());

		al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 255));

		al_draw_text(font18, al_map_rgb(0, 0, 0), (x1 + x2) / 2, (y1 + y2) / 2 - 10, ALLEGRO_ALIGN_CENTER, str);
	}
};
