

#include "Movement.h"


/**
* \brief Basic constructor for the Movement class.
* \details All the private data members are set to a safe value.
* \parm Nothing
* \return Nothing
*/

Movement::Movement(float width, float height)
{

	//currentPositionPS = 50;      //current position of player ship
	windowWidth = width;
	windowHeight = height;
}


Movement::~Movement()
{


}

//setter

void Movement::SetWindowWidth(float width)
{
	windowWidth = width;
}
//getter
float Movement::GetWindowWidth(void)
{

	return windowWidth;
}

void Movement::SetWindowHeight(float height)

{
	windowHeight = height;
}

float Movement::GetWindowHeight(void)
{

	return windowHeight;
}


//Name: PlayerMove
//Purpose: The purpose of this method is to move the ship
//			to the next set square on the grid. If the ship
//			has reached the end of the screen, it will be 
//			reset to start at the front again.
void Movement::PlayerMove(pair<float,float> mousePosition)
{
	pair <float, float> playerPosition;
	playerPosition = GetCurrentPositionPS();

	pair<float, float> cpt;

	// MOVE SHIP AUTOMATICALLY
	if (mousePosition.first == 0 && mousePosition.second == 0)
	{


		//storing the player ship positions
		cpt.first = shipBStart.first;
		cpt.second = shipBStart.second;
		SetCurrentPositionPS(cpt);
	}
	else
	{

		if (playerPosition.first < mousePosition.first)
		{
			shipBStart.first++;
			shipDStart.first++;

			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCurrentPositionPS(cpt);
		}
		if (playerPosition.first > mousePosition.first)
		{
			shipBStart.first--;
			shipDStart.first--;

			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCurrentPositionPS(cpt);
		}

		if (playerPosition.second < mousePosition.second)
		{
			shipBStart.second++;
			shipDStart.second++;

			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCurrentPositionPS(cpt);
		}
		if (playerPosition.second > mousePosition.second)
		{
			shipBStart.second--;
			shipDStart.second--;

			//storing current position
			cpt.first = shipBStart.first;
			cpt.second = shipBStart.second;
			SetCurrentPositionPS(cpt);
		}
	}

	// Restarting the Player ship on the left-side
	if (shipBStart.first > 1024 || shipBStart.second > 768
		|| shipBStart.first < 0 || shipBStart.second < 0)
	{
		shipBStart.first = 0;
		shipBStart.first = shipBStart.first++;
		shipBStart.second = 384;
		shipDStart.first = 0;
		shipDStart.first = shipDStart.second++;
		shipDStart.second = 384;

		cpt.first = shipBStart.first;
		cpt.second = shipBStart.second;
		SetCurrentPositionPS(cpt);

	}
}

pair<float, float> Movement::GetShipDStart()
{
	return shipBStart;
}
pair<float, float> Movement::GetShipBStart()
{
	return shipBStart;
}


pair<float,float> Movement::GetCurrentPositionPS()
{
	return currentPositionPS;

}

void Movement::SetCurrentPositionPS(pair<float,float> playerShipPosition)
{
	currentPositionPS = playerShipPosition;
}