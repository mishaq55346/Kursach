#pragma once
#include <string>
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

class Panel
{
	int x1, y1, x2, y2;
public:
	string text = "20";
	bool enabled = false;
	ALLEGRO_FONT *font18;
	Panel(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2)
	{
		font18 = al_load_font("arial.ttf", 18, 0);
	}
	void draw(string text)
	{
		if (this->text != text)
			this->text = text;
		if (!font18) {
			std::cout << "font18 not loaded\n";
			exit(2);
		}
		if(enabled)
			al_draw_rounded_rectangle(x1, y1, x2, y2, 6, 6, al_map_rgb(255, 255, 255), 4);
		else
			al_draw_rounded_rectangle(x1, y1, x2, y2, 6, 6, al_map_rgb(210, 210, 210), 4);

		al_draw_text(font18, al_map_rgb(255, 255, 255), (x1 + x2) / 2, (y1 + y2) / 2 - 10, ALLEGRO_ALIGN_CENTER, text.c_str());
	}
	bool isClicked(int x, int y)
	{
		return x > x1 && x < x2 && y > y1 && y < y2;
	}
};
