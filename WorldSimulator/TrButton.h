#pragma once
#include "Button.h"

class TrButton : public Button
{
private:
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	bool is_up;
	
public:
	TrButton(int x1, int y1, int x2, int y2, int x3, int y3, bool is_up) : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), is_up(is_up)
	{
	}
	void draw()
	{
		if (is_up) {
			//(100, 50, 120, 50, 110, 30, true);
			al_draw_filled_rectangle(x1 - thickness * 2, y1 + thickness * 2, x2 + thickness * 2, y3 - thickness * 2, al_map_rgb(255, 255, 255));
			al_draw_filled_rectangle(x1 - thickness, y1 + thickness, x2 + thickness, y3 - thickness, al_map_rgb(60, 60, 60));
			al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, al_map_rgb(255, 255, 255));
			//al_draw_filled_triangle(x1 + 2, y1 - 2, x2 - 2, y2 - 2, x3, y3 + 2, al_map_rgb(60, 60, 60));
		}
		else
		{
			al_draw_filled_rectangle(x1 - thickness * 2, y1 - thickness * 2, x2 + thickness * 2, y3 + thickness * 2, al_map_rgb(255, 255, 255));
			al_draw_filled_rectangle(x1 - thickness, y1 - thickness, x2 + thickness, y3 + thickness, al_map_rgb(60, 60, 60));
			al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, al_map_rgb(255, 255, 255));
			//al_draw_filled_triangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2, x3, y3 - 2, al_map_rgb(60, 60, 60));
		}
	}
	bool isClicked(int x, int y) override
	{
		
		if (is_up) {
			//std::cout << "clicked (" << x << ", " << y << "). isClicked = " << (x > x1 && x < x2 && y < y1 && y > y3) << std::endl;
			return (x > x1 && x < x2 && y > y3 && y < y1);
		}
		else {
			//std::cout << "clicked (" << x << ", " << y << "). isClicked = " << (x > x1 && x < x2 && y > y1 && y < y3) << std::endl;
			return (x > x1 && x < x2 && y > y1 && y < y3);
		}
	}


};
