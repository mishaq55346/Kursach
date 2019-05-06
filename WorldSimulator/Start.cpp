#include "Start.h"


void Start::init() {
	mouse_up = true;
	font24 = al_load_font("arial.ttf", 24, 0);
	image = al_load_bitmap("start.png");
	
	button_start = new RoundButton(298, 517, 700, 581);

	al_clear_to_color(al_map_rgb(255, 0, 0));
	draw();
	al_flip_display();
}
void Start::draw()
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_bitmap(image, 0, 0, 0);
}

void Start::logic(ALLEGRO_EVENT ev)
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
		onClick(x, y);
	}
	if (!mouse_up && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		mouse_up = true;

}

void Start::onClick(int x, int y)
{
	//string str = "x = " + to_string(x) + ", y = " + to_string(y);
	//al_show_native_message_box(display, "coordinates", "x, y", str.c_str(), NULL, ALLEGRO_MESSAGEBOX_WARN);
	if (button_start->isClicked(x, y))
		ext_code = 2;
	//if (button_continue->isClicked(x, y))
	//{
		//ext_code = -1;
	//}
}

void Start::onExit()
{
	ext_code = -1;
	button_start = nullptr;
	al_destroy_bitmap(image);
	al_destroy_font(font24);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_flip_display();
}