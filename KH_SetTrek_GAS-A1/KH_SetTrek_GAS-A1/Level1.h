#pragma once
#include "GameLevel.h"
#include "Starship.h"
#include "Grid.h"
#include "Movement.h"
#include "Vector.h"
#include <thread>
#include <chrono>

#define MINI_GAME 1
#define GAME_END -1
#define ALL_GOOD 0

class Level1 : public GameLevel
{
	float windowWidth;
	float windowHeight;
	float gridWidth;
	float gridHeight;
	/*float sectorX;
	float sectorY;*/
	bool gameStart;

	Movement* moving = new Movement(windowWidth, windowHeight);
	SpriteSheet* background;
	SpriteSheet* planet1;
	SpriteSheet* planet2;
	SpriteSheet* planet3;
	SpriteSheet* miniGameLayout;
	SpriteSheet* shipBaseTest;
	Starship* shipBase;
	Starship*  shipDetails;
	Starship* enemyShip;
	Grid* newGrid;


public:
	void Load() override;
	void Unload() override;
	int Update() override;
	void Render(bool miniGame) override;
	float GetWindowWidth(void);
	float GetWindowHeight(void);
	void SetWindowWidth(float width);
	void SetWindowHeight(float height);
	void SetShipDestination(float x, float y);
	void SetShipPosition(void);
	void IsMoveFinished(void);
	void SetEnemyPos(void);
	void SetEnemyDest(void);
	bool CheckShipCollision(void);
	bool PlanetTouched(void);
	void NewSector(void);

};
