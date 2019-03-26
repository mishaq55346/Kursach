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
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMEOUT timeout;
	bool get_event;
	bool ext = false;
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_DISPLAY_MODE disp_mode;
	const int speed = 50;//in msec per frame
	int timeUntilFinish = 200;
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
		screen_centreX = disp_modeF.width / 2;//980 //центры экрана по осям
		screen_centreY = disp_modeF.height / 2;//540
		width = 800;//
		height = 600;//

		display = al_create_display(width, height);
		al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//располагаем по центру экрана
		
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

		//готовый конфиг:
		//map[5][5] = 1;
		//map[5][6] = 1;
		//map[6][5] = 1;
		//map[6][6] = 1;
		//map[4][5] = 1;
		//map[7][5] = 1;
		//map[5][7] = 1;
		//map[8][7] = 1;

		map[2][0] = 1;
		map[2][1] = 1;
		map[2][2] = 1;
		map[1][2] = 1;
		map[0][1] = 1;//planer
		//конец конфига
	}
	int randN(int min, int max)
	{
		//TODO сделать в пределах от 50 до 255

		random_device rd;
		mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 
		return mersenne() ;
	}
	void printMap()
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));
		
		//al_draw_rectangle(0, 0, width,height, al_map_rgb(0, 0, 0), 3.0f);
		//при попытке в полноцветность выбирать для клетки преобладающий вокруг цвет

		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				if (map[i][j] != 0)
					//al_draw_filled_circle(
						//x + width / 2 - (x - i * 2) * 20,
						//y + height / 2 - (y - j * 2) * 20,
						//(x < y) ? (x - 20 / 10) : (y - 20 / 10),
						//4,
						//al_map_rgb(0, 0, 0));
					
						al_draw_filled_rectangle(
							i * (width / x),
							j * (height / y),
							(i + 1) * (width / x),
							(j + 1) * (height / y),
							//al_map_rgb(0, 0, 0),
							al_map_rgb(randN(1, 255), randN(1, 255), randN(1, 255))//,
							//1.0
						);
			}
		}
		//al_draw_text(ALLEGRO_FONT, al_map_rgb(0, 0, 0), 10, 10, 0, "w_sizeX" + std::to_string(width));
	}

	void handleClick()
	{

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
		//timeUntilFinish--;

		printMap();
		if(choosing_points)
		{
			handleClick();
		}
		else {
			Sleep(speed);
			markKill();
			giveBirth();
			applyChanges();
		}
		al_flip_display();
	}

	void exit()
	{
		al_destroy_display(display);
	}
};
