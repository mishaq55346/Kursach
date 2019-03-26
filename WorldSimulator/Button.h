#pragma once
#include <allegro5/allegro_primitives.h>
#include <string>
#include "Menu.h"

class Button
{
public:
	int thickness = 6;
	Button(){}
	virtual bool isClicked(int x, int y) = 0;
	virtual void draw() = 0;
	
};