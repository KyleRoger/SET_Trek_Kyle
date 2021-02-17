
#pragma once
#include <time.h>
#include <vector>
#include "Graphics.h"
#include "SpriteSheet.h"
using namespace std;


class Grid
{
private:

	float windowWidth;				//!< The width of the window
	float windowHeight;				//!< The height of the window

	float gridWidth;				//!< The width of 1 grid
	float gridHeight;				//!< The height of 1 grid

	int numOfRows;					//!< The number of rows that comprises of the grid
	int numOfCols;					//!< The number of cols that comprises of the grid


public:

	pair<float, float> coordinates;
	pair< int, int> selectedPlanetLocID;
	vector<pair<float, float>> grid;			//!< Contains the absolute position for the 10 by 10 grid. There are 100 squares in total
	vector<pair<float, float>> selectCoord;		//!< Contains the grid coordinates of where a random planet may spawn
	vector <pair <int, int>> PlanetLocations;  //strore picked grid value and corrosponding planet to place

	//-Constructors
	Grid(void);
	Grid(float windowWidth, float windowHeight);

	//-Destructors
	~Grid(void);

	//-Methods
	void ConstructGrid(void);
	void CreateRandomCoordinates(void);

	//-Accessors
	float GetWindowWidth(void) const;
	float GetWindowHeight(void) const;

	float GetWidth(void) const;
	float GetHeight(void) const;

	int GetNumRows(void) const;
	int GetNumCols(void) const;

	int GetGridNum(void) const;
	int GetRandCoordSize(void) const;

	vector<pair<float, float>> GetGrid(void) const;
	vector<pair<float, float>> GetRandCoord(void) const;
	void PlanetRandomize(SpriteSheet* planet1, SpriteSheet* planet2, SpriteSheet* planet);
};