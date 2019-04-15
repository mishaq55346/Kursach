#pragma once
#include "Button.h"

class RoundButton : public Button
{
public:
	int x1, y1, x2, y2;
	RoundButton(int x1, int y1, int x2, int y2) : x1(x1), x2(x2), y1(y1), y2(y2)
	{
	}
	RoundButton() : x1(0), x2(0), y1(0), y2(0)
	{
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
	
	
};
