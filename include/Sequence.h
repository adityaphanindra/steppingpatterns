///
/// \file Sequence.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Settings.h"
#include "MarkerData.h"

#include <vector>

using namespace std;

///
/// \class Sequence
/// \brief Sequence Class
///
class Sequence
{
private:
	uint				_sequenceNumber; 			///< sequence number
	
public:
	///
	/// \brief Constructor
	/// \param sequenceNumber: sequence number
	///
	Sequence(uint sequenceNumber);

	///
	/// \brief get orientation from foot markers
	/// \param markers: marker data
	/// \return orientation wrt x-axis
	///
	static float getFootOrientation(vector<Marker::MarkerData> markers);

	///
	/// \brief get orientation from pelvis markers
	/// \param markers: marker data
	/// \return orientation wrt x-axis
	///
	static float getPelvisOrientation(vector<Marker::MarkerData> markers);

private:
};


#endif