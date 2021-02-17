#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::Loading;

void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true; //This can help us avoid loading activity while rendering
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}

void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->Unload();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}

void GameController::Render(bool miniGame)
{
	if (Loading) return;//nice! Do not update or render if the scene is loading.
	currentLevel->Render(miniGame);
}

int GameController::Update()
{
	int gameState = 0;

	if (Loading)
	{
		return gameState; //nice! Do not update or render if the scene is loading.
	}
	else
	{
		gameState = currentLevel->Update();
		return gameState;
	}
}