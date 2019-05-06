#include "Menu.h"
#include "Game.h"
#include "Select.h"
#include "Start.h"
#include "Tile.h"
#include <allegro5/allegro_ttf.h>
#include <algorithm>

//#include <vld.h>

//�������� ���������� ���. ����
//�������:
//���� � ������ 2-3 ������� - ��� �����������. ����� ������
//���� � ����� ������ ���� 3 �������� ����� - �� ���� ������ ��������� ��������
//0 - �����
//1 - ���� ��������
//2 - ����� �� ���� ���
//3 - ������� �� ���� ���


//TODO ������� �������� �� ���������� ���������
//TODO ������ �������� ����� ����. ��� �������� � �����

//TODO ---������� ��� ���� ���� � �����������
//TODO ---� ���������� ���������� ���������� ������

//TODO ������� ����� �� �����(�� �������������� �����, � �� �� ��������)
//TODO �������� shared_ptr �� ��� �������-������

using namespace std;

void migrate(Select sel, Game *game);

enum GameState { S_Start, S_Menu, S_Select, S_Game, S_Finish };
GameState State;

ALLEGRO_TIMEOUT timeout;

Start start;
Menu menu;
Select sel;
Game game;

void print(vector<Point> points)
{
	for (auto p : points)
		cout << p.x << "---" << p.y << endl;
	cout << "---------------\n";
}
void print(vector<Tile> tiles)
{
	for (auto t : tiles)
		t.print();
	cout << "======\n";
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

	State = S_Start;

	//

	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMEOUT timeout;
	
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_DISPLAY_MODE disp_modeF;
	ALLEGRO_TIMER *timer;
	int screen_centreX;
	int screen_centreY;
	const int width = 1000;
	const int height = 600;



	al_get_display_mode(al_get_num_display_modes() - 1, &disp_modeF);
	screen_centreX = disp_modeF.width / 2;//980 //������ ������ �� ����
	screen_centreY = disp_modeF.height / 2;//540

	display = al_create_display(width, height);
	al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//����������� �� ������ ������

	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_init_timeout(&timeout, 0.1);
	al_start_timer(timer);

	display = al_create_display(width, height);
	al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//����������� �� ������ ������

	
	

	
	
	
	
	

	ALLEGRO_BITMAP *logo = al_load_bitmap("logo.png");
	al_set_display_icon(display, logo);
	//

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
				al_wait_for_event_until(queue, &ev, &timeout);
				start.logic(ev);
			}
			if (start.ext_code == 1)
				State = S_Finish;
			if (start.ext_code == 2)
				State = S_Menu;
			al_rest(0.1);
			start.onExit();
			break;
		}
		case(S_Menu):
		{
			menu.init();
			while (menu.ext_code == -1) {
				al_wait_for_event_until(queue, &ev, &timeout);
				menu.logic(ev);
			}
			if (menu.ext_code == 1)
				State = S_Finish;
			if (menu.ext_code == 2)
				State = S_Select;
			if (menu.ext_code == 3)
				State = S_Start;
			al_rest(0.1);
			menu.onExit();
			break;
		}
		case(S_Select):
		{
			sel.init(menu.x, menu.y);
			while (sel.ext_code == -1) {
				al_wait_for_event_until(queue, &ev, &timeout);
				sel.logic(ev);
			}
			if (sel.ext_code == 1)
				State = S_Finish;
			if (sel.ext_code == 2)
				State = S_Game;
			if (sel.ext_code == 3)
				State = S_Menu;
			al_rest(0.1);
			sel.onExit();
			break;
		}
		case (S_Game):
		{
			game.init(sel.x, sel.y);
			migrate(sel, &game);
			while (game.ext_code == -1) {
				al_wait_for_event_until(queue, &ev, &timeout);
				game.logic(ev);
			}
			if (game.ext_code == 1)
				State = S_Finish;
			if (game.ext_code == 3)
				State = S_Select;
			if (game.ext_code == 4)
				State = S_Menu;
			al_rest(0.1);
			game.onExit();
			break;
		}
		default:;
		}
	}
	al_uninstall_mouse();
	al_uninstall_keyboard();
	return 0;
}

void migrate(Select sel, Game *game)
{
	game->tiles.clear();
	for (int i = 0; i < sel.x; ++i)
	{
		for (int j = 0; j < sel.y; ++j)
		{
			if(sel.map[i][j] == 1)
				if (!game->tiles.empty())
					game->tiles.emplace_back(i, j, game->getDominateColor(i,j));
				else
					game->tiles.emplace_back(i, j);
		}
	}
}