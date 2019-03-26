#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <Windows.h>
#include "Button.h"
#include <vector>
#include "RoundButton.h"
#include "TrButton.h"
#include "Panel.h"

using namespace std;

class Menu
{
	
public:

	ALLEGRO_EVENT_QUEUE *disp_queue;
	ALLEGRO_EVENT_QUEUE *mouse_queue;
	ALLEGRO_EVENT event_disp;
	ALLEGRO_EVENT event_mouse;
	ALLEGRO_TIMEOUT timeout;

	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_FONT *font36;
	ALLEGRO_FONT *font24;
	ALLEGRO_FONT *font18;

	vector<TrButton> t_buttons;
	RoundButton *button_start;
	TrButton *button_x_up;
	TrButton *button_y_up;
	TrButton *button_x_down;
	TrButton *button_y_down;
	Panel *panel_x;
	Panel *panel_y;
	int width = 800;
	int height = 600;
	bool get_event;
	int ext_code = -1;
	bool mouse_up = true;
	int x = 20;
	int y = 20;

	void init(){


		al_get_display_mode(al_get_num_display_modes() - 1, &disp_modeF);

		display = al_create_display(width, height);
		al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//располагаем по центру экрана
		al_clear_to_color(al_map_rgb(255, 255, 255));

		disp_queue = al_create_event_queue();
		mouse_queue = al_create_event_queue();
		al_register_event_source(disp_queue, al_get_display_event_source(display));
		al_register_event_source(mouse_queue, al_get_mouse_event_source());
		button_x_up = new TrButton(
			width/2 - 18 - 300, 
			height/2 + 20 - 100 - 40,

			width / 2 + 18 - 300, 
			height / 2 + 20 - 100 - 40,

			width / 2 - 300, 
			height / 2 - 20 - 100 - 40,
			true);
		button_x_down = new TrButton(
			width / 2 - 18 - 300,
			height / 2 - 20 - 100 + 40,

			width / 2 + 18 - 300,
			height / 2 - 20 - 100 + 40,

			width / 2 - 300,
			height / 2 + 20 - 100 + 40,
			false);
		button_y_up = new TrButton(
			width / 2 - 18 + 300,
			height / 2 + 20 - 100 - 40,

			width / 2 + 18 + 300,
			height / 2 + 20 - 100 - 40,

			width / 2 + 300,
			height / 2 - 20 - 100 - 40,
			true);
		button_y_down = new TrButton(
			width / 2 - 18 + 300,
			height / 2 - 20 - 100 + 40,

			width / 2 + 18 + 300,
			height / 2 - 20 - 100 + 40,

			width / 2 + 300,
			height / 2 + 20 - 100 + 40,
			false);
		
		panel_x = new Panel(width / 2 - 70 - 180, height / 2 - 30 - 100, width / 2 + 70 - 180, height / 2 + 30 - 100);
		panel_y = new Panel(width / 2 - 70 + 180, height / 2 - 30 - 100, width / 2 + 70 + 180, height / 2 + 30 - 100);

		button_start = new RoundButton(width / 2 - 100, height / 2 - 40 + 200, width / 2 + 100, height / 2 + 40 + 200);
		
		//TODO спросить о том как это сделать
		//button_x_up->run = [&]() { x += 2; };
		
		
		t_buttons.push_back(*button_x_up);
		t_buttons.push_back(*button_y_up);
		t_buttons.push_back(*button_x_down);
		t_buttons.push_back(*button_y_down);
	}
	void draw()
	{
		al_clear_to_color(al_map_rgb(110, 110, 110));
		for (TrButton tr_button : t_buttons)
			tr_button.draw();
		panel_x->draw(to_string(x));
		panel_y->draw(to_string(y));
		button_start->draw();
		al_flip_display();
	}
	void logic()
	{
		draw();
		al_init_timeout(&timeout, 0.01);
		al_wait_for_event_until(disp_queue, &event_disp, &timeout);
		al_wait_for_event_until(mouse_queue, &event_mouse, &timeout);
		
		if (event_disp.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			ext_code = 1;
		}
		if(mouse_up && event_mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouse_up = false;
			al_clear_to_color(al_map_rgb(255, 0, 0));
			int x = event_mouse.mouse.x;
			int y = event_mouse.mouse.y;
			onClick(x, y);
		}
		if (!mouse_up && event_mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			mouse_up = true;
	}

	void startGame()
	{
		exitA();
		ext_code = 0;
	}

	void exitA()
	{
		al_destroy_display(display);
		al_destroy_event_queue(mouse_queue);
		al_destroy_event_queue(disp_queue);
		al_destroy_font(panel_x->font18);
		al_destroy_font(panel_y->font18);
	}
	void onClick(int x, int y)
	{
		if (button_x_up->isClicked(x, y))
			Menu::x++;
		if (button_y_up->isClicked(x, y))
			Menu::y++;
		if (button_x_down->isClicked(x, y) && Menu::x > 1)
			Menu::x--;
		if (button_y_down->isClicked(x, y) && Menu::y > 1)
			Menu::y--;
		if (button_start->isClicked(x, y))
			startGame();
		cout << Menu::x << " " << Menu::y << endl;
	}

	
	
};

