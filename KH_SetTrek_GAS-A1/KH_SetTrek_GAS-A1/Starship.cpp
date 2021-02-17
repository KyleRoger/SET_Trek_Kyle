
#include "Starship.h"
#include <d2d1_1.h>

Starship::Starship(Graphics* graphics)
{
	xCoordinate = 0.0;
	yCoordinate = 0.0;
	shipEnergy = 900;
	shipScience = 0;
	shipTempScience = 0.0;
	shipTempEnergy = 0.0;
	isMoving = false;
	firstMovement = true;
	shipVector = new Vector();
	// Get a reference to the Graphics class
	gfx = graphics;

	// Initialize other data members to default values
	bmp = nullptr;
	chromaKeyEffect = nullptr;
	image = nullptr;
}


Starship::~Starship()
{
	if (image)
	{
		delete image;
		image = nullptr;
	}
}


void Starship::InitImage(const wchar_t* filename)
{
	image = new SpriteSheet(filename, gfx);
}

//Name: ShipChromakey
//Purpose: To chroma out the green screen background. Takes in the
//			RGB values to know what to take out.
void Starship::ShipChromaKey(float r, float g, float b)
{
	gfx->GetDeviceContext()->CreateEffect(CLSID_D2D1ChromaKey, &chromaKeyEffect);
	bmp = image->GetBitmap();
	chromaKeyEffect->SetInput(0, bmp);
	chromaKeyEffect->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(r, g, b));
	chromaKeyEffect->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.2f);
	chromaKeyEffect->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	chromaKeyEffect->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);
}

void Starship::Draw(float left, float top, float orientation)
{

	gfx->GetDeviceContext()->DrawImage(chromaKeyEffect,
		D2D1::Point2F(left, top));
	//gfx->GetDeviceContext()->SetTransform(D2D1::Matrix3x2F::Rotation(orientation, D2D1::Point2F(left, top)));
	
}

float Starship::GetXCoordinate()
{
	return xCoordinate;
}

float Starship::GetYCoordinate()
{
	return yCoordinate;
}

void Starship::SetXCoordinate(float x)
{
	xCoordinate = x;
}

void Starship::SetYCoordinate(float y)
{
	yCoordinate = y;
}

void Starship::SetXDest(float x)
{
	xDest = x;
}

void Starship::SetYDest(float y)
{
	yDest = y;
}

float Starship::GetXDest(void)
{
	return xDest;
}

float Starship::GetYDest(void)
{
	return yDest;
}
bool Starship::GetFirstMovement()
{
	return firstMovement;
}

void Starship::SetFirstMovement()
{
	firstMovement = false;
}

Vector* Starship::GetVector()
{
	return shipVector;
}

void Starship::SetOrientation()
{
	const float PI = 3.1415926;
	shipOrientation = atan2(yDest - yCoordinate, xDest - xCoordinate) * (180 / PI);
}
float Starship::GetOrientation()
{
	return shipOrientation;
}

bool Starship::GetIsMoving()
{
	return isMoving;
}

void Starship::SetIsMoving(bool moving)
{
	isMoving = moving;
}

void Starship::SetEnergy(float energy)
{
	shipEnergy = energy;
}

float Starship::GetEnergy()
{
	return shipEnergy;
}

void Starship::SetScience(float science)
{
	shipScience = science;
}
float Starship::GetScience(void)
{
	return shipScience;
}

void Starship::SetTempEnergy(float energy)
{
	shipTempEnergy = energy;
}

float Starship::GetTempEnergy()
{
	return shipTempEnergy;
}

void Starship::SetTempScience(float science)
{
	shipTempScience = science;
}
float Starship::GetTempScience(void)
{
	return shipTempScience;
}