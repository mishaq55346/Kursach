#include "Menu.h"

void Menu::init() {
	mouse_up = true;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_modeF);

	display = al_create_display(width, height);
	al_set_window_position(display, disp_modeF.width / 2 - width / 2, disp_modeF.height / 2 - height / 2);//располагаем по центру экрана
	al_clear_to_color(al_map_rgb(255, 255, 255));

	image = al_load_bitmap("menu.png");

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	panel_x = new Panel(131, 157, 370, 225);
	panel_y = new Panel(631, 157, 870, 225);

	button_back = new RoundButton(95, 520, 406, 580);
	button_continue = new RoundButton(594, 520, 905, 580);

}
void Menu::draw()
{
	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_draw_bitmap(image, 0, 0, 0);
	panel_x->draw(panel_x->text);
	panel_y->draw(panel_y->text);
	//button_continue->draw();
	al_flip_display();
}

void Menu::logic()
{
	draw();
	al_wait_for_event_until(event_queue, &event, &timeout);

	if(event.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		//if(event.type == ALLEGRO_KEY_BACKSPACE)
		//if(event.type == ALLEGRO_KEY_DPAD_UP)
		int keycode = 0;
		keycode = event.keyboard.keycode;
		if (keycode >= ALLEGRO_KEY_0 && keycode <= ALLEGRO_KEY_9)//27-36 vkluchit
		{
			if (panel_x->enabled)
				if(panel_x->text == "0")
					panel_x->text = to_string(keycode - ALLEGRO_KEY_0);
				else
					panel_x->text += to_string(keycode - ALLEGRO_KEY_0);
			else if (panel_y->enabled)
				if (panel_y->text == "0")
					panel_y->text = to_string(keycode - ALLEGRO_KEY_0);
				else
					panel_y->text += to_string(keycode - ALLEGRO_KEY_0);
		}
		else if (keycode == ALLEGRO_KEY_BACKSPACE)
			if (panel_x->enabled && panel_x->text.size() > 0) {
				panel_x->text.erase((panel_x->text.size() - 1), 1);
				if (panel_x->text.size() == 0)
					panel_x->text = "0";
			}
			else if (panel_y->enabled && panel_y->text.size() > 0) {
				panel_y->text.erase((panel_y->text.size() - 1), 1);
				if (panel_y->text.size() == 0)
					panel_y->text = "0";
			}
		if (panel_x->text != to_string(x))
			x = atoi(panel_x->text.c_str());
		if (panel_y->text != to_string(y))
			y = atoi(panel_y->text.c_str());
	}
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
	}
	if (!mouse_up && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		mouse_up = true;
}

void Menu::onExit()
{
	ext_code = -1;
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(panel_x->font18);
	al_destroy_font(panel_y->font18);
	al_destroy_bitmap(image);
}

void Menu::onClick(int x, int y)
{

	if (panel_x->isClicked(x, y) && !panel_x->enabled) {
		panel_x->enabled = true;
		panel_y->enabled = false;
		event.type = 0;
	}
	if (panel_y->isClicked(x, y) && !panel_y->enabled) {
		panel_y->enabled = true;
		panel_x->enabled = false;
		event.type = 0;
	}
	if (button_continue->isClicked(x, y)) {
		if ((this->x / (float)this->y) >= 3 || (this->y / (float)this->x) >= 3)
		{
			al_show_native_message_box(al_get_current_display(), "Error", "Unproportional size of the field",
				"One side of the field can't be bigger of the other at 3 or more times", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			mouse_up = true;
		}
		else if (this->x > 2 && this->y > 2 && this->x < 100 && this->y < 100) {
			ext_code = 2;
			event.type = 0;
		}
		else
		{
			al_show_native_message_box(al_get_current_display(), "Error", "Invalid width or height",
				"Width and Height must be more than 2 and less than 100 tiles", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			mouse_up = true;
		}
	}
	if (button_back->isClicked(x, y)) {
		ext_code = 3;
		event.type = 0;
	}
}
