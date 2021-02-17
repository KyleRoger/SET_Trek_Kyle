#pragma once


class Mouse
{
public:

	static float mouseX;
	static float mouseY;
	static float keyboardSelection;
	static float EnergyLevel;
	static void Init(void);
	static bool IsClick;
	Mouse(float x, float y, bool isClick);
};