#include "Start.h"


void Start::init() {
	mouse_up = true;
	font24 = al_load_font("arial.ttf", 24, 0);
	image = al_load_bitmap("start.png");
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_modeF);
	screen_centreX = disp_modeF.width / 2;//980 //центры экрана по осям
	screen_centreY = disp_modeF.height / 2;//540
	width = 1000;//
	height = 600;//

	display = al_create_display(width, height);
	al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//располагаем по центру экрана

	disp_queue = al_create_event_queue();
	mouse_queue = al_create_event_queue();

	al_register_event_source(disp_queue, al_get_display_event_source(display));
	al_register_event_source(mouse_queue, al_get_mouse_event_source());
	
	al_init_timeout(&timeout, 0.01);

	button_start = new RoundButton(298, 517, 700, 581, al_map_rgb(0, 0, 0));

	al_clear_to_color(al_map_rgb(255, 0, 0));
	draw();
}
void Start::draw()
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_bitmap(image, 0, 0, 0);
}

void Start::logic()
{
	al_flip_display();
	al_wait_for_event_until(mouse_queue, &event_mouse, &timeout);
	al_wait_for_event_until(disp_queue, &event_disp, &timeout);
	if (event_disp.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		ext_code = 1;
	}
	if (mouse_up && event_mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		mouse_up = false;
		int x = event_mouse.mouse.x;
		int y = event_mouse.mouse.y;
		onClick(x, y);
	}
	if (!mouse_up && event_mouse.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		mouse_up = true;

}

void Start::onClick(int x, int y)
{
	//string str = "x = " + to_string(x) + ", y = " + to_string(y);
	//al_show_native_message_box(display, "coordinates", "x, y", str.c_str(), NULL, ALLEGRO_MESSAGEBOX_WARN);
	if (button_start->isClicked(x, y))
		ext_code = 2;
	//if (button_start->isClicked(x, y))
	//{
		//ext_code = -1;
	//}
}

void Start::onExit()
{
	ext_code = -1;
	al_destroy_display(display);
	al_destroy_event_queue(mouse_queue);
	al_destroy_event_queue(disp_queue);
	al_destroy_bitmap(image);
	al_destroy_font(font24);
}