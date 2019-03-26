#include "Menu.h"
#include "Game.h"
#include "Select.h"




//правила:
//если у клетки 2-3 соседей - она сохран€етс€. иначе смэрть
//если у любой клетки есть 3 животных р€дом - на этой клетке рождаетс€ животное
//0 - пусто
//1 - есть животное
//2 - умрет на след ход
//3 - родитс€ на след ход
using namespace std;

void migrate(Select sel, Game game);
char toUpper(char ch);

Menu menu;
Select sel;
Game game;

int main()
{
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();


	//menu.init();
	//while (menu.ext_code == -1) {
	//	menu.logic();//запуск менюшки
	//}
	//if(menu.ext_code != 0)
	//	return 1;

	//sel.init(menu.x, menu.y);
	sel.init(20, 20);
	while (sel.ext_code == -1) 
		sel.logic();//«апуск окна выбора клеток
	sel.exit();
	//game.init(menu.x, menu.y);
	
	game.init(20, 20);
	migrate(sel, game);
	while (game.timeUntilFinish > 0) {
		game.logic();//запуск самой игры
	}

	game.exit();
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