///
/// \file Subject.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "Subject.h"
#include "C3DReader.h"

// --------------------------------------------------------- Constructors
Subject::Subject(uint subjectNumber) :
	_subjectNumber(subjectNumber)
{
	_c3dDirectory = "..//data//c3d//" + intToString(subjectNumber);
}

// --------------------------------------------------------- Public Functions
void Subject::setThresholds(Subject::Thresholds thresholds)
{
	_thresholds = thresholds;
}

void Subject::calibrate()
{
	string pCalibFileName = _c3dDirectory + "//Body.c3d";
	string lCalibFileName = _c3dDirectory + "//Left.c3d";
	string rCalibFileName = _c3dDirectory + "//Right.c3d";
	
	C3D::C3DReader reader(NUM_MARKERS, FRAME_RATE);
	/*std::vector<std::map<uint, std::unique_ptr<Marker::MarkerData> > > pelvisCalib = reader.readAllFrames(pCalibFileName);
	std::vector<std::map<uint, std::unique_ptr<Marker::MarkerData> > > leftFootCalib = reader.readAllFrames(lCalibFileName);
	std::vector<std::map<uint, std::unique_ptr<Marker::MarkerData> > > rightFootCalib = reader.readAllFrames(rCalibFileName);*/

	 
}