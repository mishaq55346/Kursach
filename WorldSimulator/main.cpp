#include "Menu.h"
#include "Game.h"
#include "Select.h"
#include "Start.h"
#include <allegro5/allegro_ttf.h>

#include <vld.h>

//вписываю ассистента каф. ИППО
//правила:
//если у клетки 2-3 соседей - она сохраняется. иначе смэрть
//если у любой клетки есть 3 животных рядом - на этой клетке рождается животное
//0 - пусто
//1 - есть животное
//2 - умрет на след ход
//3 - родится на след ход


//TODO сделать проверку на стабильное состояние

//TODO сделать еще одно окно с инструкцией
//TODO в инструкции нарисовать устойчивые фигуры

//TODO перевести все на рельсы классов(обрабатывать только живые клетки: каждую клетку представить в виде объекта)
//TODO исправить задержку в классе Game
//TODO сделать цвета по генам

using namespace std;

void migrate(Select sel, Game game);
char toUpper(char ch);

enum GameState { S_Start, S_Menu, S_Select, S_Game, S_Finish };
GameState State;

ALLEGRO_TIMEOUT timeout;

Start start;
Menu menu;
Select sel;
Game game;

int main()
{
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();

	State = S_Menu;

	//ext_code?
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
			while (start.ext_code == -1)
				start.logic();
			if (start.ext_code == 1)
				State = S_Finish;
			if (start.ext_code == 2)
				State = S_Menu;
			start.onExit();
			break;
		}
		case(S_Menu):
		{
			menu.init();
			while (menu.ext_code == -1)
				menu.logic();
			if (menu.ext_code == 1)
				State = S_Finish;
			if (menu.ext_code == 2)
				State = S_Select;
			if (menu.ext_code == 3)
				State = S_Start;
			menu.onExit();
			break;
		}
		case(S_Select):
		{
			sel.init(menu.x, menu.y);
			while (sel.ext_code == -1)
				sel.logic();
			if (sel.ext_code == 1)
				State = S_Finish;
			if (sel.ext_code == 2)
				State = S_Game;
			if (sel.ext_code == 3)
				State = S_Menu;
			sel.onExit();
			break;
		}
		case (S_Game):
		{
			game.init(sel.x, sel.y);
			migrate(sel, game);
			while (game.ext_code == -1)
				game.logic();
			if (game.ext_code == 1)
				State = S_Finish;
			if (game.ext_code == 3)
				State = S_Select;
			if (game.ext_code == 4)
				State = S_Menu;
			game.onExit();
			break;
		}
		default:;
		}
	}
	return 0;

}

void migrate(Select sel, Game game)
{
	for (int i = 0; i < sel.x; ++i)
	{
		for (int j = 0; j < sel.y; ++j)
		{
			game.map[i][j] = sel.map[i][j];
		}
	}
}

char toUpper(char ch)
{
	if (ch >= 'a'&&ch <= 'z')
		return (char)(ch - 32);
	return ch;
}