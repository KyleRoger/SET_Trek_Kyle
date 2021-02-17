#pragma once
#include <Windows.h>
#include "Grid.h"
#include "Graphics.h"
using namespace std;

class Movement
{
private:

	float windowWidth;
	float windowHeight;
	float gridWidth;
	float gridHeight;

	pair<float,float> currentPositionPS;      //get the current position of player ship

	pair<float, float> shipBStart;              //direction of shipbase
	pair<float, float> shipDStart;			//Ship details direction

public:

	Movement(float windowWidth, float windowHeight);

	~Movement(void);

	pair<float, float> GetShipDStart();
	pair<float, float> GetShipBStart();
	


	void SetWindowWidth(float width);
	void SetWindowHeight(float height);
	pair<float,float> GetCurrentPositionPS();
	Grid* moveGrid;
	Grid* planetGrid = new Grid(windowWidth, windowHeight);


	void SetCurrentPositionPS(pair<float,float> playerShipPosition);

	void PlayerMove(pair<float, float> mousePosition);

	//-Getters
	float GetWindowWidth(void);
	float GetWindowHeight(void);
};