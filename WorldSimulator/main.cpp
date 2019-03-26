#include "Menu.h"
#include "Game.h"
#include "Select.h"




//�������:
//���� � ������ 2-3 ������� - ��� �����������. ����� ������
//���� � ����� ������ ���� 3 �������� ����� - �� ���� ������ ��������� ��������
//0 - �����
//1 - ���� ��������
//2 - ����� �� ���� ���
//3 - ������� �� ���� ���
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
	//	menu.logic();//������ �������
	//}
	//if(menu.ext_code != 0)
	//	return 1;

	//sel.init(menu.x, menu.y);
	sel.init(20, 20);
	while (sel.ext_code == -1) 
		sel.logic();//������ ���� ������ ������
	sel.exit();
	//game.init(menu.x, menu.y);
	
	game.init(20, 20);
	migrate(sel, game);
	while (game.timeUntilFinish > 0) {
		game.logic();//������ ����� ����
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