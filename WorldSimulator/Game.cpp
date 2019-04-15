#include "Game.h"

void eventListener(ALLEGRO_EVENT event, int x1_1, int y1_1)
{

}

void Game::init(int x, int y) {
	mouse_up = true;
	this->x = x;
	this->y = y;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_modeF);
	screen_centreX = disp_modeF.width / 2;//980 //центры экрана по осям
	screen_centreY = disp_modeF.height / 2;//540

	image = al_load_bitmap("game.png");

	display = al_create_display(width, height);
	al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//располагаем по центру экрана
	event_queue = al_create_event_queue();

	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	al_start_timer(timer);

	button_back = RoundButton(95, 520, 405, 580);
	button_main_menu = RoundButton(595, 520, 905, 580);

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

	
	//thread thr(eventListener, event);
	//thr.detach();

	
}

int Game::randN(int min, int max)
{
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 
	return mersenne();
}

void Game::draw(){
	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_draw_bitmap(image, 0, 0, 0);
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			if (map[i][j] != 0)
				al_draw_filled_rectangle(
					28 + i * ((width - 27 - 28) / (float)x),
					97 + j * ((height - 110 - 97) / (float)y),
					28 + (i + 1) * ((width - 27 - 28) / (float)x),
					97 + (j + 1) * ((height - 110 - 97) / (float)y),
					al_map_rgb(randN(1, 255), randN(1, 255), randN(1, 255))//
				);
		}
	}
	al_flip_display();
}

int Game::nCount(int i, int j){
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

void Game::logic(){

	al_wait_for_event(event_queue, &event);

	cout << event.type << endl;

	if (redraw) {
		redraw = false;
		draw();
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			ext_code = 1;
		}
		if (mouse_up && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouse_up = false;
			int x = event.mouse.x;
			int y = event.mouse.y;
			onClick(x, y);
			mouse_up = false;
		}
		if (!mouse_up && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			mouse_up = true;
		markKill();
		giveBirth();
		applyChanges();
	}

	if (event.type == ALLEGRO_EVENT_TIMER) {
		redraw = true;
	}

	
	
}

void Game::onClick(int x, int y) 
{
	if (button_back.isClicked(x, y))
	{
		ext_code = 3;
		event.type = 0;// нужно для багфикса двойного клика
	}
	else if (button_main_menu.isClicked(x, y))
	{
		ext_code = 4;
		event.type = 0;// нужно для багфикса двойного клика
	}
	//al_show_native_message_box(display, "", "", ("(" + to_string(x) + ";" + to_string(y) + ")").c_str(), NULL, 0);
}

void Game::markKill()
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
void Game::giveBirth()
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
void Game::applyChanges() const
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

void Game::onExit()
{
	ext_code = -1;
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(image);
}
