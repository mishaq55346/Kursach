#include "Select.h"
#include <allegro5/allegro_native_dialog.h>

void Select::init(int x, int y) {
	mouse_up = true;

	this->x = x;
	this->y = y;
	
	image = al_load_bitmap("select.png");

	//al_clear_to_color(al_map_rgb(255, 0, 0));

	button_back = new RoundButton(95, 520, 405, 580);
	button_continue = new RoundButton(595, 520, 905, 580);
	
	map = new int*[x];
	for (int i = 0; i < x; ++i)
	{
		map[i] = new int[y];
		for (int j = 0; j < y; ++j)
		{
			map[i][j] = 0;
		}
	}
	draw();
}
void Select::draw()
{
	//al_clear_to_color(al_map_rgb(255, 0, 0));

	al_draw_bitmap(image, 0, 0, 0);

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			if (map[i][j] != 0)
				al_draw_filled_circle(
					28 + (i + 0.5) * ((width - 27 - 28) / (float)x),
					 97 + (j + 0.5) * ((height - 110 - 97) / (float)y),
					//(y > x) ? ((height + 97 - 110) / (float)y / 4) : ((width + 27 - 28) / (float)x / 4),
					4,
					al_map_rgba(70, 70, 70, 0));

			al_draw_rectangle(
				28 + i * ((width - 27 - 28) / (float)x),
				97 + j * ((height - 110 - 97) / (float)y),
				28 + (i + 1) * ((width - 27 - 28) / (float)x),
				97 + (j + 1) * ((height - 110 - 97) / (float)y),
				al_map_rgba(70, 70, 70,0),
				1.0
			);
		}
	}
	
	al_flip_display();
}

void Select::logic(ALLEGRO_EVENT ev)
{
	
	
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
	}
	if (!mouse_up && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		mouse_up = true;
}

void Select::onClick(int x, int y, ALLEGRO_EVENT ev)
{
	if (button_continue->isClicked(x, y))
	{
		ext_code = 2;
	}
	if (button_back->isClicked(x, y))
	{
		ext_code = 3;
	}
	else {
		int i = (x - 28) / ((width - 27 - 28) / (float)Select::x);
		int j = (y - 97) / ((height - 110 - 97) / (float)Select::y);
		map[i][j] = !map[i][j];
	}
	ev.type = 0;
	draw();
}

void Select::onExit()
{
	ext_code = -1;
	al_destroy_bitmap(image);
	//al_clear_to_color(al_map_rgb(255, 0, 0));
}
