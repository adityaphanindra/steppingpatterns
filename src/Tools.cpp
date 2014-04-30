///
/// \file Tools.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Tools.h"
#include "Settings.h"

float wrapToPi(float input)
{
	float sign = 1.0;
	if(input < 0)
		sign = -1.0;
	input = sign * fmod(input, 2 * PI);
	if(input > PI)
		return input - 2 * PI;
	else if(input <= -PI)
		return 2 * PI + input;
	else
		return input;
}

float wrapTo180(float input)
{
	float sign = 1.0;
	if(input < 0)
		sign = -1.0;
	input = sign * fmod(input, 360);
	if(input > 180)
		return input - 360;
	else if(input <= -180)
		return 360 + input;
	else
		return input;
}

float degToRad(float input)
{
	return wrapToPi(input * PI / 180.0);
}

float radToDeg(float input)
{
	return wrapTo180(input * 180.0 / PI);
}