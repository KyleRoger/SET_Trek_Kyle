#include "Mouse.h"


float Mouse::mouseX;
float Mouse::mouseY;
float Mouse::keyboardSelection;

bool Mouse::IsClick;


void Mouse::Init(void)
{

	mouseX = 0.0;
	mouseY = 0.0;
	keyboardSelection = 0;
	IsClick = false;
}

Mouse::Mouse(float x, float y, bool isClick)
{

	mouseX = x;
	mouseY = y;
	IsClick = isClick;
}