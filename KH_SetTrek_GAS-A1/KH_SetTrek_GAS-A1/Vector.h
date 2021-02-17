#pragma once
#include <iostream>
#include <complex>

class Vector
{
private:
	float xVectorLen;
	float yVectorLen;
	float xRat;
	float yRat;
	float vectorMagnitude;

public:

	void XVectorLength(float a, float b);
	void YVectorLength(float a, float b);

	float GetXVectorLength();
	float GetYVectorLength();
	float GetXRatio();
	float GetYRatio();
	float GetMagnitude();
	void VectorMagnitude(float xVector, float yVector);
	void FrameRatio(float xVector, float yVector);
};