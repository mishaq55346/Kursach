#include "Game.h"

void Game::init(int x, int y) {
	mouse_up = true;
	this->x = x;
	this->y = y;

	image = al_load_bitmap("game.png");

	button_back = RoundButton(95, 520, 405, 580);
	button_main_menu = RoundButton(595, 520, 905, 580);

	//al_clear_to_color(al_map_rgb(0, 255, 0));


}

int Game::randN()
{
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 
	return mersenne();
}

void Game::draw() {
	//al_clear_to_color(al_map_rgb(255, 0, 0));
	al_draw_bitmap(image, 0, 0, 0);
	for (auto tile : tiles)
	{
		al_draw_filled_rectangle(
			28 + tile.x * ((width - 27 - 28) / (float)x),
			97 + tile.y * ((height - 110 - 97) / (float)y),
			28 + (tile.x + 1) * ((width - 27 - 28) / (float)x),
			97 + (tile.y + 1) * ((height - 110 - 97) / (float)y),
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
	//находит кол-во тайлов-соседов
	int count = 0;
	for (auto tile : tiles) {
		if (x == tile.x && y == tile.y)
			continue;
		int distance_x = min(abs(tile.x - x) % this->x, abs(this->x - (abs(tile.x - x) % this->x)));
		int distance_y = min(abs(tile.y - y) % this->y, abs(this->y - (abs(tile.y - y) % this->y)));
		//cout << x << " " << y << " tile: distance from (" << tile.x << ", " << tile.y << ") tile = (" <<  distance_x << ", " << distance_y << ")" << endl;
		if (
			(distance_x == 1 || distance_x == 0) && (distance_y == 1 || distance_y == 0)
			)
			count++;
	}
	return count;
}

vector<Tile> Game::getTNeighbours(int x, int y) {//функция обратная поиску выше: поиск "живых" тайлов в радиусе 1 клетки и возврат их количества
	//находит кол-во тайлов-соседов
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
				(this->y + tile.y) % this->y
			);
	}
	return temp;
}

void Game::logic(ALLEGRO_EVENT ev) {
	draw();
	cout << ev.type << endl;
	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		ext_code = 1;
	}
	if (mouse_up && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		mouse_up = false;
		int x = ev.mouse.x;
		int y = ev.mouse.y;
		onClick(x, y, ev);
		mouse_up = false;
	}
	if (!mouse_up && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		mouse_up = true;
	if (redraw) {
		redraw = false;
		markKill();
		giveBirth();
		applyChanges();
		//findAnomalies();
		//здесь апдейт игры
	}
	if (ev.type == ALLEGRO_EVENT_TIMER)
		redraw = true;
}

void Game::findAnomalies()
{
	for (auto t : tiles)
		if (count(tiles.begin(), tiles.end(), t) > 1) {
			cerr << "found anomaly on tile: ";
			t.print();
			cerr << "found 2 or more tiles of one type in vector." << endl;
		}
}

void Game::onClick(int x, int y, ALLEGRO_EVENT ev)
{
	if (button_back.isClicked(x, y))
	{
		ext_code = 3;
		ev.type = 0;// нужно для багфикса двойного клика
	}
	else if (button_main_menu.isClicked(x, y))
	{
		ext_code = 4;
		ev.type = 0;// нужно для багфикса двойного клика
	}
	//al_show_native_message_box(display, "", "", ("(" + to_string(x) + ";" + to_string(y) + ")").c_str(), NULL, 0);
}

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

ALLEGRO_COLOR Game::getDominateColor(int x, int y)
{
	vector<Tile> temp = getTNeighbours(x, y);

	if (temp.empty()) {
		return al_map_rgb(randN(), randN(), randN());
	}
	float r = 0;
	float g = 0;
	float b = 0;
	int size = temp.size();
	for (auto tile : temp)
	{
		r += tile.color.r / size;
		g += tile.color.g / size;
		b += tile.color.b / size;
	}
	return al_map_rgb(r * 255.0, g * 255.0, b * 255.0);
}

void Game::onExit()
{
	ext_code = -1;
	tiles.clear();
	al_destroy_bitmap(image);
	//al_clear_to_color(al_map_rgb(0, 255, 0));
	al_flip_display();
}
