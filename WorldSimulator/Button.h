#pragma once

class Button
{
public:
	int thickness = 6;
	Button() {}
	virtual bool isClicked(int x, int y) = 0;
};