#include "Menu.h"

void Menu::init() {
	mouse_up = true;
	image = al_load_bitmap("menu.png");

	panel_x = new Panel(131, 157, 370, 225);
	panel_y = new Panel(631, 157, 870, 225);

	button_back = new RoundButton(95, 520, 406, 580);
	button_continue = new RoundButton(594, 520, 905, 580);

	x = 20;
	y = 20;

}
void Menu::draw()
{
	//al_clear_to_color(al_map_rgb(255, 0, 0));
	al_draw_bitmap(image, 0, 0, 0);
	panel_x->draw(panel_x->text);
	panel_y->draw(panel_y->text);
	//button_continue->draw();
	al_flip_display();
}

void Menu::logic(ALLEGRO_EVENT ev)
{
	draw();
	if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		//if(ev.type == ALLEGRO_KEY_BACKSPACE)
		//if(ev.type == ALLEGRO_KEY_DPAD_UP)
		int keycode = 0;
		keycode = ev.keyboard.keycode;
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

void Menu::onExit()
{
	ext_code = -1;
	al_destroy_font(panel_x->font18);
	al_destroy_font(panel_y->font18);
	al_destroy_bitmap(image);
	//al_clear_to_color(al_map_rgb(255, 0, 0));
	al_flip_display();
}

void Menu::onClick(int x, int y, ALLEGRO_EVENT ev)
{

	if (panel_x->isClicked(x, y) && !panel_x->enabled) {
		panel_x->enabled = true;
		panel_y->enabled = false;
		ev.type = 0;
	}
	if (panel_y->isClicked(x, y) && !panel_y->enabled) {
		panel_y->enabled = true;
		panel_x->enabled = false;
		ev.type = 0;
	}
	if (button_continue->isClicked(x, y)) {
		if ((this->x / (float)this->y) >= 2 || (this->y / (float)this->x) >= 2)
		{
			al_show_native_message_box(al_get_current_display(), "Error", "Unproportional size of the field",
				"One side of the field can't be bigger of the other at 2 or more times", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			mouse_up = true;
		}
		else if (this->x > 2 && this->y > 2 && this->x < 100 && this->y < 100) {
			ext_code = 2;
			ev.type = 0;
		}
		else
		{
			al_show_native_message_box(al_get_current_display(), "Error", "Invalid width or height",
				"Width and Height must be more than 2 and less than 100 tiles", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			mouse_up = true;
		}
	}
	ev.type = 0;
	if (button_back->isClicked(x, y)) {
		ext_code = 3;
		ev.type = 0;
	}
}
