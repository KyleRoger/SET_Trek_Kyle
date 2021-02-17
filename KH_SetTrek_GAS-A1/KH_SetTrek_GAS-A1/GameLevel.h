#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"

class GameLevel
{
protected:
	static Graphics* gfx;

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual int Update() = 0;
	virtual void Render(bool miniGame) = 0;
};