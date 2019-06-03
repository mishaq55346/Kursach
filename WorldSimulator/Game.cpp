#include "Game.h"

void Game::init(int x, int y) {
	mouse_up = true;
	this->x = x;
	this->y = y;
	epic_music = false;
	colors[0] = al_map_rgb(255, 0, 0);//red
	colors[1] = al_map_rgb(0, 255, 0);//green
	colors[2] = al_map_rgb(0, 0, 255);//blue
	colors[3] = al_map_rgb(0, 255, 255);//aqua
	colors[4] = al_map_rgb(255, 0, 255);//fuchsia
	colors[5] = al_map_rgb(255, 255, 0);//yellow
	colors[6] = al_map_rgb(255, 255, 255);//white

	image = al_load_bitmap("game.png");

	al_reserve_samples(1);
	audio_full = al_load_sample("full.wav");

	button_back = RoundButton(95, 520, 405, 580);
	button_main_menu = RoundButton(595, 520, 905, 580);

	stable = false;
	al_play_sample(audio_full, 1.0, 0.0, 1.1, ALLEGRO_PLAYMODE_LOOP, 0);
	music_event_queue = al_create_event_queue();
	music_timer = al_create_timer(14.6);
	al_register_event_source(music_event_queue, al_get_timer_event_source(music_timer));
	al_init_timeout(&music_timeout, 0.1);
	al_start_timer(music_timer);
}

int Game::randN()
{
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 
	return (mersenne());
}

void Game::draw() {
	al_draw_bitmap(image, 0, 0, 0);
	for (const auto tile : tiles)
	{
		if (epic_music) {
			al_draw_filled_rectangle(
				28 + tile.x * ((width - 27 - 28) / float(x)),//28 и 97 - поправки для края экрана
				97 + tile.y * ((height - 110 - 97) / float(y)),
				28 + (tile.x + 1) * ((width - 27 - 28) / float(x)),
				97 + (tile.y + 1) * ((height - 110 - 97) / float(y)),
				colors[abs(randN() % 7)]//
			);
		}
		else
			al_draw_filled_rectangle(
				28 + tile.x * ((width - 27 - 28) / float(x)),//28 и 97 - поправки для края экрана
				97 + tile.y * ((height - 110 - 97) / float(y)),
				28 + (tile.x + 1) * ((width - 27 - 28) / float(x)),
				97 + (tile.y + 1) * ((height - 110 - 97) / float(y)),
				tile.color//
			);
	}
	al_flip_display();
}

vector<Point> Game::getPNeighbours(int x, int y) {//функция поиска "мертвых" окружающих тайлов(в радиусе 1 клетки) и их возврат в векторе точек
	vector<Point> neighbours = {};
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++) {
			if (i == x && j == y)//не дает чекать самого себя
				continue;
			if (
				find(tiles.begin(), tiles.end(), Tile((this->x + i % this->x) % this->x, (this->y + j % this->y) % this->y, Tile::T_Born)) == tiles.end() &&
				find(tiles.begin(), tiles.end(), Tile((this->x + i % this->x) % this->x, (this->y + j % this->y) % this->y, Tile::T_Live)) == tiles.end() &&
				find(tiles.begin(), tiles.end(), Tile((this->x + i % this->x) % this->x, (this->y + j % this->y) % this->y, Tile::T_Dyeing)) == tiles.end()
				)//если этого тайла нет в векторе
				neighbours.emplace_back(
				(this->x + i) % this->x,
					(this->y + j) % this->y
				);//добавляем его
		}
	return neighbours;
}

int Game::getTNeighboursCount(int x, int y) {//функция обратная поиску выше: поиск "живых" тайлов в радиусе 1 клетки и возврат их количества
	int count = 0;
	for (const auto tile : tiles) {
		if (x == tile.x && y == tile.y)
			continue;
		const int distance_x = min(abs(tile.x - x) % this->x, abs(this->x - (abs(tile.x - x) % this->x)));
		const int distance_y = min(abs(tile.y - y) % this->y, abs(this->y - (abs(tile.y - y) % this->y)));
		if (
			(distance_x == 1 || distance_x == 0) && (distance_y == 1 || distance_y == 0)
			)
			count++;
	}
	return count;
}

vector<Tile> Game::getTNeighbours(int x, int y) {//функция обратная поиску выше: поиск "живых" тайлов в радиусе 1 клетки и возврат их количества
	vector<Tile> temp;
	for (auto tile : tiles) {
		if (x == tile.x && y == tile.y)
			continue;
		int distance_x = min(abs(tile.x - x) % this->x, abs(this->x - (abs(tile.x - x) % this->x)));
		int distance_y = min(abs(tile.y - y) % this->y, abs(this->y - (abs(tile.y - y) % this->y)));
		//cout << x << " " << y << " tile: distance from (" << tile.x << ", " << tile.y << ") tile = (" << distance_x << ", " << distance_y << ")" << endl;
		if (
			(distance_x == 1 || distance_x == 0) && (distance_y == 1 || distance_y == 0)
			)
			temp.emplace_back(
			(this->x + tile.x) % this->x,
				(this->y + tile.y) % this->y,
				tile.color
			);
	}
	return temp;
}

void Game::logic(ALLEGRO_EVENT ev) {
	if(!stable)
		draw();//отрисовываем поле
	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//если закрываем окно, выходим с кодом 1
	{
		ext_code = 1;
	}
	if (mouse_up && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)//если мышь была поднята и опустилась - фиксируем клик
	{
		mouse_up = false;//предотвращаем повторное срабатывание клика
		int x = ev.mouse.x;
		int y = ev.mouse.y;//заносим координаты клика
		onClick(x, y, ev);//обрабатываем клик
	}
	if (!mouse_up && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)//если мышь была опущена и поднялась - фиксируем поднятие мыши
		mouse_up = true;
	if (!stable && relogic) {//если надо отрисовать новый ход - обрабатываем логику
		relogic = false;
		previousStates.push_back(tiles);
		if (previousStates.size() >= 4)
			previousStates.pop_front();
		markKill();//помечаем клетки, что нужно "убить"
		giveBirth();//помечаем клетки, что скоро родятся
		applyChanges();//подтверждаем изменения клеток - убитых уничтожаем, родившихся утверждаем

		list<vector<Tile>>::iterator it;
		int period = 0;
		for (it = previousStates.begin(); it != previousStates.end(); ++it) {
			period++;
			if (*it == tiles)
			{
				al_show_native_message_box(
					al_get_current_display(),
					"WOW",
					"Stable state found",
					("That the end my friend, try another configuration, period is " + to_string(previousStates.size() - period + 1)).c_str(),
					nullptr, 
					ALLEGRO_MESSAGEBOX_WARN
				);
				stable = true;
				ev.type = 0;
			}
		}
	}
	if(!epic_music)
	al_wait_for_event_until(music_event_queue, &music_event, &music_timeout);
	if (!epic_music && music_event.type == ALLEGRO_EVENT_TIMER) {
		epic_music = true;
		music_event.type = 0;
		al_destroy_timer(music_timer);
	}
	if (ev.type == ALLEGRO_EVENT_TIMER)
		relogic = true;//по тику таймера обновляем картинку
	ev.type = 0;//обновляем тип ивента
}

void Game::onClick(int x, int y, ALLEGRO_EVENT ev)
{
	if (button_back.isClicked(x, y))
	{
		ext_code = 3;
	}
	else if (button_main_menu.isClicked(x, y))
	{
		ext_code = 4;
	}
}

//"Сердце программы" - все операции с клетками, проводимые каждый ход
void Game::markKill()
{
	for (auto &tile : tiles) {
		const int count = getTNeighboursCount(tile.x, tile.y);
		if (count < 2 || count > 3)
			tile.State = Tile::T_Dyeing;
	}
}
void Game::giveBirth()
{
	vector<Tile> birth_tiles = {};
	for (const auto tile : tiles)
	{
		vector<Point> neighbours = getPNeighbours(tile.x, tile.y);
		for (auto p : neighbours)
			if (getTNeighboursCount(p.x, p.y) == 3 && (find(birth_tiles.begin(), birth_tiles.end(), Tile(p.x, p.y, Tile::T_Born)) == birth_tiles.end()))
				birth_tiles.emplace_back(p.x, p.y, Tile::T_Born, getDominateColor(p.x, p.y));
	}
	for (auto &t : birth_tiles)
		tiles.emplace_back(t);
}
void Game::applyChanges()
{
	vector<Tile> temp = tiles;
	for (auto &tile : tiles)
		if (tile.State == Tile::T_Dyeing)
			temp.erase(remove(temp.begin(), temp.end(), tile));
	for (auto &tile : temp)
		if (tile.State == Tile::T_Born)
			tile.State = Tile::T_Live;
	tiles = temp;
	temp.clear();
}

//функции сравнения 2х цветов
bool operator==(const ALLEGRO_COLOR& left, const ALLEGRO_COLOR& right)
{
	return(left.r == right.r && left.g == right.g && left.b == right.b);
}
bool operator!=(const ALLEGRO_COLOR& left, const ALLEGRO_COLOR& right)
{
	return(left.r != right.r || left.g != right.g || left.b != right.b);
}

//функция поиска индекса максимального элемента в массиве чисел размера size
int indexOfMax(int *mas, int size)
{
	int max_i = 0;
	for (int i = 1; i < size; ++i)
	{
		if (mas[i] > mas[max_i])
			max_i = i;
	}
	return max_i;
}

ALLEGRO_COLOR Game::getDominateColor(int x, int y)
{
	int c[7]{ 0,0,0,0,0,0,0 };//количество каждого цвета вокруг текущей клетки
	vector<Tile> neighbours = getTNeighbours(x, y);//находим всех соседей
	if(neighbours.empty())//если вокруг никого нет - ставим клетке рандомный цвет
	{
		const int rand = abs(randN() % 7);//берем рандомное положительное число не превышающее размер массива цветов
		return colors[rand];//возвращаем рандомный элемент массива цветов
	}
	//если вокруг клетки есть соседи
	for(auto tile : neighbours)//проходим по каждому соседу
	{
		if (tile.color == colors[0])//сравниваем цвет соседа с цветом из массива цветов
			c[0]++;//если такой есть, увеличиваем 0й элемент массива интов на 1
		else if (tile.color == colors[1])
			c[1]++;
		else if (tile.color == colors[2])
			c[2]++;
		else if (tile.color == colors[3])
			c[3]++;
		else if (tile.color == colors[4])
			c[4]++;
		else if (tile.color == colors[5])
			c[5]++;
		else if (tile.color == colors[6])
			c[6]++;
	}

	const int maxColor = indexOfMax(c, 7);//смотрим, какого цвета в округе больше
	return colors[maxColor];//возвращаем доминирующий цвет
}


void Game::onExit()
{
	ext_code = -1;
	tiles.clear();
	if(image != nullptr)
		al_destroy_bitmap(image);
	music_event.type = 0;
	al_destroy_sample(audio_full);
	al_stop_samples();
}
