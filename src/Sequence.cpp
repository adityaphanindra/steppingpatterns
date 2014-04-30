///
/// \file Sequence.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Sequence.h"
#include "Settings.h"
#include <cmath>

// --------------------------------------------------------- Constructors
Sequence::Sequence(uint sequenceNumber) :
	_sequenceNumber(sequenceNumber)
{
}


// --------------------------------------------------------- Public static functions
float Sequence::getFootOrientation(vector<Marker::MarkerData> markers)
{
	return atan2(markers[FOOT_TOP].getPosition().y - markers[FOOT_BOTTOM].getPosition().y, markers[FOOT_TOP].getPosition().x - markers[FOOT_BOTTOM].getPosition().x);
}

float Sequence::getPelvisOrientation(vector<Marker::MarkerData> markers)
{
	return atan2(markers[PELVIS_RIGHT].getPosition().y - markers[PELVIS_LEFT].getPosition().y, markers[PELVIS_RIGHT].getPosition().x - markers[PELVIS_LEFT].getPosition().x) + PI;
}


