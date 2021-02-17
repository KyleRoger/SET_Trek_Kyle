#pragma once
#include <Windows.h>
#include <vector>
#include <time.h>
#include <wincodec.h>
#include "Graphics.h"
#include "SpriteSheet.h"
#include "GameLevel.h"
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <d3d11_1.h>
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>
#include "Vector.h"

using namespace std;

class Starship
{
private:

	Graphics* gfx; //Reference to the Graphics class
	ID2D1Bitmap* bmp; //This will hold our loaded and converted Bitmap file
	ID2D1Effect* chromaKeyEffect;
	SpriteSheet* image;
	float xCoordinate;
	float yCoordinate;
	float shipEnergy;
	float shipScience;
	bool isMoving;
	bool firstMovement;
	float xDest;
	float yDest;
	Vector* shipVector;
	float shipOrientation;
	float shipTempScience;
	float shipTempEnergy;

public:

	Starship(Graphics* gfx);
	~Starship();

	void InitImage(const wchar_t* filename);
	void ShipChromaKey(float r, float g, float b);

	void Draw(float left, float top, float orientation);
	float GetXCoordinate(void);
	float GetYCoordinate(void);
	void SetXCoordinate(float x);
	void SetYCoordinate(float y);
	bool GetFirstMovement(void);
	void SetFirstMovement(void);

	void SetXDest(float x);
	void SetYDest(float y);
	float GetXDest(void);
	float GetYDest(void);
	bool GetIsMoving(void);
	void SetIsMoving(bool moving);
	void SetEnergy(float energy);
	float GetEnergy(void);
	void SetScience(float science);
	float GetScience(void);
	void SetTempScience(float science);
	float GetTempScience(void);
	void SetTempEnergy(float energy);
	float GetTempEnergy(void);

	Vector* GetVector();
	void SetOrientation();
	float GetOrientation();
};