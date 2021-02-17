
#include "Vector.h"

void Vector::XVectorLength(float a, float b)
{
	xVectorLen = a - b;
}

void Vector::YVectorLength(float a, float b)
{
	yVectorLen = a - b;
}

float Vector::GetXRatio() 
{
	return xRat;
}

float Vector::GetYRatio()
{
	return yRat;
}

float Vector::GetXVectorLength()
{
	return xVectorLen;
}

float Vector::GetYVectorLength()
{
	return yVectorLen;
}

float Vector::GetMagnitude()
{
	return vectorMagnitude;
}

void Vector::VectorMagnitude(float xVector, float yVector)
{
	std::complex<float> vectorComplex(xVector, yVector);
	vectorMagnitude = std::abs(vectorComplex);
}
void Vector::FrameRatio(float xVector, float yVector)
{
	VectorMagnitude(xVectorLen, yVectorLen);

	if (vectorMagnitude != 0)
	{
		xRat = xVectorLen / vectorMagnitude;
		yRat = yVectorLen / vectorMagnitude;
	}
}