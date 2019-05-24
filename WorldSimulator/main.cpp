#include "Windows.h"
#include "Menu.h"
#include "Game.h"
#include "Select.h"
#include "Start.h"
#include "Tile.h"
#include <allegro5/allegro_ttf.h>
#include <algorithm>
#include <list>
#include <vector>
#include <queue>

//#include <vld.h>


//правила:
//если у клетки 2-3 соседей - она сохраняется. иначе смэрть
//если у любой клетки есть 3 животных рядом - на этой клетке рождается животное
//0 - пусто
//1 - есть животное
//2 - умрет на след ход
//3 - родится на след ход




//TODO ---сделать еще одно окно с инструкцией
//TODO ---в инструкции нарисовать устойчивые фигуры

using namespace std;

void migrate(Select sel, Game *game);
void migrate(Select *sel, Game *game);

enum GameState { S_Start, S_Menu, S_Select, S_Game, S_Finish };
GameState State;

Start start;
Menu menu;
Select sel;
Game game;

ALLEGRO_EVENT_QUEUE *e_queue;
ALLEGRO_EVENT ev;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_DISPLAY_MODE disp_modeF;
ALLEGRO_TIMER *timer;
int screen_centreX;
int screen_centreY;
const int width = 1000;
const int height = 600;

void allegro_init()
{
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_modeF);
	screen_centreX = disp_modeF.width / 2;//980 //центры экрана по осям
	screen_centreY = disp_modeF.height / 2;//540

	display = al_create_display(width, height);
	al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//располагаем по центру экрана

	e_queue = al_create_event_queue();

	timer = al_create_timer(0.1);

	al_register_event_source(e_queue, al_get_display_event_source(display));
	al_register_event_source(e_queue, al_get_mouse_event_source());
	al_register_event_source(e_queue, al_get_keyboard_event_source());
	al_register_event_source(e_queue, al_get_timer_event_source(timer));

	al_init_timeout(&timeout, 0.1);
	al_start_timer(timer);

	ALLEGRO_BITMAP *logo = al_load_bitmap("logo.png");
	al_set_display_icon(display, logo);
}

int main()
{
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();

	State = S_Start;

	allegro_init();
	
	//ext_code = ?
	//-1 - continue process
	//1 - exit
	//2 - next
	//3 - prev
	//4 - main menu

	while (State != S_Finish)
	{
		switch (State) {
		case(S_Start):
		{
			start.init();
			while (start.ext_code == -1) {
				al_wait_for_event_until(e_queue, &ev, &timeout);
				start.logic(ev);
			}
			if (start.ext_code == 1)
				State = S_Finish;
			if (start.ext_code == 2)
				State = S_Menu;
			ev.type = 0;
			al_rest(0.1);
			start.onExit();
			break;
		}
		case(S_Menu):
		{
			menu.init();
			while (menu.ext_code == -1) {
				al_wait_for_event_until(e_queue, &ev, &timeout);
				menu.logic(ev);
			}
			if (menu.ext_code == 1)
				State = S_Finish;
			if (menu.ext_code == 2)
				State = S_Select;
			if (menu.ext_code == 3)
				State = S_Start;
			ev.type = 0;
			al_rest(0.1);
			menu.onExit();
			break;
		}
		case(S_Select):
		{
			sel.init(menu.x, menu.y);
			while (sel.ext_code == -1) {
				al_wait_for_event_until(e_queue, &ev, &timeout);
				sel.logic(ev);
			}
			if (sel.ext_code == 1)
				State = S_Finish;
			if (sel.ext_code == 2)
				State = S_Game;
			if (sel.ext_code == 3)
				State = S_Menu;
			ev.type = 0;
			al_rest(0.1);
			sel.onExit();
			break;
		}
		case (S_Game):
		{
			game.init(sel.x, sel.y);
			migrate(sel, &game);
			while (game.ext_code == -1) {
				al_wait_for_event_until(e_queue, &ev, &timeout);
				game.logic(ev);
				ev.type = 0;
			}
			if (game.ext_code == 1)
				State = S_Finish;
			if (game.ext_code == 3) {
				State = S_Select;
			}
			if (game.ext_code == 4)
				State = S_Menu;
			ev.type = 0;
			al_rest(0.1);
			game.onExit();
			break;
		}
		default:;
		}
	}
	al_destroy_display(display);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	
	return 0;
}

void migrate(Select sel, Game *game)//from select to game
{
	game->tiles.clear();
	for (auto t : sel.tiles)
		game->tiles.emplace_back(t.x, t.y, game->getDominateColor(t.x, t.y));
}