#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <Windows.h>
#include "Menu.h"
#include <string>
//#include <random>
#include "random"

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
	bool get_event;
	int ext_code = -1;
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_DISPLAY_MODE disp_mode;
	RoundButton *button;
	ALLEGRO_FONT *font24;

	const int speed = 50;//in msec per frame
	int timeUntilFinish = 200;
	int **map = new int*[0];

	int scale = 20;

	bool mouse_up = true;

	int screen_centreX;
	int screen_centreY;
	int width;
	int height;
	int b_corr;

	void init(int x, int y) {
		font24 = al_load_font("arial.ttf", 24, 0);
		this->x = x;
		this->y = y;
		al_get_display_mode(al_get_num_display_modes() - 1, &disp_modeF);
		screen_centreX = disp_modeF.width / 2;//980 //центры экрана по осям
		screen_centreY = disp_modeF.height / 2;//540
		width = 800;//
		height = 800;//

		display = al_create_display(width, height);
		al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//располагаем по центру экрана

		disp_queue = al_create_event_queue();
		mouse_queue = al_create_event_queue();
		al_register_event_source(disp_queue, al_get_display_event_source(display));
		al_register_event_source(mouse_queue, al_get_mouse_event_source());

		al_clear_to_color(al_map_rgb(255, 0, 0));

		button = new RoundButton(200, 650, 600, 750);

		map = new int*[x];
		for (int i = 0; i < x; ++i)
		{
			map[i] = new int[y];
			for (int j = 0; j < y; ++j)
			{
				map[i][j] = 0;
			}
		}
	}
	void printMap()
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));

		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				if (map[i][j] != 0)
					al_draw_filled_circle(
						(i + 1.5) * (width / x),
						(j + 1.5) * ((height - 200) / y),
						//(x < y) ? (x - 20 / 10) : (y - 20 / 10),
						height / y / 4,
						al_map_rgb(0, 0, 0));

					al_draw_rectangle(
						i * (width / x),
						j * ((height - 200) / y),
						(i + 1) * (width / x),
						(j + 1) * ((height - 200) / y),
						al_map_rgb(0, 0, 0),
						1.0
					);
			}
		}
		button->drawAlternative();
		al_draw_text(font24, al_map_rgb(0, 0, 0), 400, 685, ALLEGRO_ALIGN_CENTER, "Begin simulation");
		al_draw_line(0, 600, 800, 600, al_map_rgb(0, 0, 0), 6);
	}

	void logic()
	{
		printMap();
		al_init_timeout(&timeout, 0.01);
		al_wait_for_event_until(disp_queue, &event_disp, &timeout);
		al_wait_for_event_until(mouse_queue, &event_mouse, &timeout);

		if (event_disp.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			ext_code = 1;
		}
		if (mouse_up && event_mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouse_up = false;
			int x = event_mouse.mouse.x;
			int y = event_mouse.mouse.y;
			onClick(x, y);
		}
		if (!mouse_up && event_mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			mouse_up = true;
		al_flip_display();
	}

	

	void onClick(int x, int y)
	{
		if(button->isClicked(x, y))
		{
			ext_code = 0;
		}
		int i = ((int)x / (int)(width / Select::x) - 1);
		int j = ((int)y / (int)((height - 200) / Select::y) - 1);
		map[i][j] = !map[i][j];
	}

	void exit()
	{
		al_destroy_display(display);
		al_destroy_event_queue(mouse_queue);
		al_destroy_event_queue(disp_queue);
	}
};
