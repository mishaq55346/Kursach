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

class Game
{
private:
	int x = 10;
	int y = 10;
public:
	ALLEGRO_EVENT event_disp;
	ALLEGRO_EVENT_QUEUE *disp_queue;
	ALLEGRO_TIMEOUT timeout;
	bool get_event;
	int ext_code = -1;
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_DISPLAY_MODE disp_mode;
	const int speed = 50;//in msec per frame
	int **map = new int*[0];

	int scale = 20;

	int screen_centreX;
	int screen_centreY;
	int width;
	int height;
	int b_corr;

	void init(int x, int y) {
		this->x = x;
		this->y = y;
		al_get_display_mode(al_get_num_display_modes() - 1, &disp_modeF);
		screen_centreX = disp_modeF.width / 2;//980 //������ ������ �� ����
		screen_centreY = disp_modeF.height / 2;//540
		width = 800;//
		height = 600;//

		display = al_create_display(width, height);
		al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//����������� �� ������ ������
		disp_queue = al_create_event_queue();
		al_register_event_source(disp_queue, al_get_display_event_source(display));
		
		al_clear_to_color(al_map_rgb(60, 60, 60));
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
	int randN(int min, int max)
	{
		//TODO ������� � �������� �� 50 �� 255
		random_device rd;
		mt19937 mersenne(rd()); // �������������� ����� �������� ��������� ��������� ������ 
		return mersenne() ;
	}
	void printMap()
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				if (map[i][j] != 0)
					al_draw_filled_rectangle(
						i * (width / x),
						j * (height / y),
						(i + 1) * (width / x),
						(j + 1) * (height / y),
						al_map_rgb(randN(1, 255), randN(1, 255), randN(1, 255))//,
					);
			}
		}
	}

	int nCount(int i, int j)
	{
		int count = 0;

		if ((map[(x + i + 1) % x][(y + j) % y] == 1) || (map[(x + i + 1) % x][(y + j) % y] == 2))
			count++;
		if ((map[(x + i + 1) % x][(y + j + 1) % y] == 1) || (map[(x + i + 1) % x][(y + j + 1) % y] == 2))
			count++;
		if ((map[(x + i) % x][(y + j + 1) % y] == 1) || (map[(x + i) % x][(y + j + 1) % y] == 2))
			count++;
		if ((map[(x + i - 1) % x][(y + j + 1) % y] == 1) || (map[(x + i - 1) % x][(y + j + 1) % y] == 2))
			count++;
		if ((map[(x + i - 1) % x][(y + j) % y] == 1) || (map[(x + i - 1) % x][(y + j) % y] == 2))
			count++;
		if ((map[(x + i - 1) % x][(y + j - 1) % y] == 1) || (map[(x + i - 1) % x][(y + j - 1) % y] == 2))
			count++;
		if ((map[(x + i) % x][(y + j - 1) % y] == 1) || (map[(x + i) % x][(y + j - 1) % y] == 2))
			count++;
		if ((map[(x + i + 1) % x][(y + j - 1) % y] == 1) || (map[(x + i + 1) % x][(y + j - 1) % y] == 2))
			count++;
		return count;
	}
	void markKill()
	{
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{

				if (map[i][j] == 1) {
					int count = nCount(i, j);
					if (count < 2 || count > 3)
						map[i][j] = 2;
				}
			}

		}
	}
	void giveBirth()
	{
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				if (map[i][j] == 0 && nCount(i, j) == 3)
					map[i][j] = 3;
			}
		}
	}
	void applyChanges()
	{
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				if (map[i][j] == 2)
					map[i][j] = 0;
				if (map[i][j] == 3)
					map[i][j] = 1;
			}
		}
	}

	bool choosing_points = false;

	void logic()
	{

		printMap();
		al_init_timeout(&timeout, 0.01);
		al_wait_for_event_until(disp_queue, &event_disp, &timeout);
		if (event_disp.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			ext_code = 1;
		}
		Sleep(speed);
		markKill();
		giveBirth();
		applyChanges();
		al_flip_display();
	}

	void exit()
	{
		al_destroy_display(display);
	}
};
