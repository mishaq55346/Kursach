#pragma once
#include "Button.h"

class RoundButton : public Button
{
	int x1, y1, x2, y2;
public:
	RoundButton(int x1, int y1, int x2, int y2) : x1(x1), x2(x2),y1(y1), y2(y2)
	{
	};
	void draw()
	{
		al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 6, 6, al_map_rgb(255, 255, 255));
		al_draw_filled_rounded_rectangle(x1 + thickness, y1 + thickness, x2 - thickness, y2 - thickness, 4, 4, al_map_rgb(60, 60, 60));
	}
	void drawAlternative()
	{
		al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 6, 6, al_map_rgb(60, 60, 60));
		al_draw_filled_rounded_rectangle(x1 + thickness, y1 + thickness, x2 - thickness, y2 - thickness, 4, 4, al_map_rgb(255, 255, 255));
	}

	int getCentreX()
	{
		return (x1 + x2) / 2;
	}
	int getCentreY()
	{
		return (y1 + y2) / 2;
	}

	bool isClicked(int x, int y) override
	{
		return x > x1 && x < x2 && y > y1 && y < y2;
	}
	bool isHover(int x, int y)
	{
		return x > x1 && x < x2 && y > y1 && y < y2;
	}
	
};
