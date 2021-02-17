
#include "Grid.h"



Grid::Grid(void)
{
	windowWidth = 0.0f;
	windowHeight = 0.0f;
	gridWidth = 0.0f;
	gridHeight = 0.0f;

	numOfRows = 0;
	numOfCols = 0;
}


Grid::Grid(float width, float height)
{
	windowWidth = width;
	windowHeight = height;
	gridWidth = windowWidth / 10;
	gridHeight = windowHeight / 10;

	numOfRows = 0;
	numOfCols = 0;
}


/**
* \brief Destructor for the Grid object.
*/
Grid::~Grid(void)
{
}



void Grid::ConstructGrid(void)
{
	int row = 0;
	int col = 0;

	for (row = 0; row < 10; ++row)
	{
		for (col = 0; col < 10; ++col)
		{
			coordinates.first = col * gridWidth;
			coordinates.second = row * gridHeight;
			grid.push_back(coordinates);
		}
	}
}


void Grid::CreateRandomCoordinates(void)
{
	srand((unsigned)time(NULL));
	int planetSpawn = 0;
	selectCoord.clear();


	for (int i = 0; i < grid.size(); ++i)
	{

			planetSpawn = (rand() % 20 + 1);

			if (planetSpawn == 10)
			{
				coordinates.first = grid[i].first;
				coordinates.second = grid[i].second;
				selectCoord.push_back(coordinates);
			}
	}
}

//Name: Planet Locations
//Purpose: The purpose of this method is to randomly assign a planet to the
//			corresponding grid location that planets are going to be 
//			populated for. This method creates a vecor that contains a pair.
//			This pairs initial number corresponding to the grid index, the
//			second number is the choice in planet.
void Grid::PlanetRandomize(SpriteSheet* planet1, SpriteSheet* planet2, SpriteSheet* planet3)
{
	srand((unsigned)time(NULL));
	int randomPlanet = 0; //Will correspond to one of three random planets.
	int index = 0; //Will correspond to the current grid location

	//Loop through selectCoord which contains the randomly selected
	//grid coordinate locations that are going to populated with planets.
	for (index = 0; index < selectCoord.size(); index++)
	{
		randomPlanet = (rand() % 3 + 1); //Give the planets a value of 1,2,3
										//corresponding to different planets.

		selectedPlanetLocID.first = index; //Index is the grid location.
		selectedPlanetLocID.second = randomPlanet;//The planet to display.
		PlanetLocations.push_back(selectedPlanetLocID); //Pair placed in vector.
	}

	for (int i = 0; i < selectCoord.size(); i++)
	{

		if (PlanetLocations[i].second == 1)
		{
			planet1->DrawPlanet(selectCoord[i].first, selectCoord[i].second);
		}
		if (PlanetLocations[i].second == 2)
		{
			planet2->DrawPlanet(selectCoord[i].first, selectCoord[i].second);
		}
		if (PlanetLocations[i].second == 3)
		{
			planet3->DrawPlanet(selectCoord[i].first, selectCoord[i].second);
		}
	}
}


float Grid::GetWindowWidth(void) const {
	return windowWidth;
}
float Grid::GetWindowHeight(void) const {
	return windowHeight;
}

float Grid::GetWidth(void) const {
	return gridWidth;
}
float Grid::GetHeight(void) const {
	return gridHeight;
}

int Grid::GetNumRows(void) const {
	return numOfRows;
}
int Grid::GetNumCols(void) const {
	return numOfCols;
}

int Grid::GetGridNum(void) const {
	return (int)grid.size();
}
int Grid::GetRandCoordSize(void) const {
	return (int)selectCoord.size();
}

vector<pair<float, float>> Grid::GetGrid(void) const {
	return grid;
}
vector<pair<float, float>> Grid::GetRandCoord(void) const {
	return selectCoord;
}