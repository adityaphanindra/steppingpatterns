///
/// \file C3DReader.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "C3DReader.h"
#include <fstream>

using namespace C3D;

C3DReader::C3DReader(uint numMarkers, uint frameRate) : 
	_numMarkers(numMarkers), 
	_frameRate(frameRate)
{
	std::string fileName = "..//data//Sample.c3d";
	std::ifstream sampleFileIn(fileName);
	if(sampleFileIn)
		_fileInfo = new UuIcsC3d::C3dFileInfo(fileName);
	else
		std::cerr << "C3D::C3DReader::C3DReader(): Cannot find ..//data//Sample.c3d" << std::endl;
}

void C3DReader::writeToC3D(std::string fileName, std::vector<UuIcsC3d::FrameData> data)
{
	bool success = UuIcsC3d::write(fileName, *_fileInfo, data, get_pointer(UuIcsC3d::get_native_io()));

	if(DEBUG)
		if(!success)
			std::cout << "C3D::C3DReader::writeToC3D(): Cannot write to the file: " << fileName << std::endl;
}

std::vector<std::map<uint, Marker::MarkerData > > C3DReader::readAllFrames(std::string fileName)
{
	UuIcsC3d::C3dFileInfo inFileInfo(fileName);
	uint inFrameCount = inFileInfo.frame_count();
	std::vector< std::map<uint, Marker::MarkerData > > frameMarkerData;

	if (inFrameCount == 0) 
	{
		std::cerr << "There are no frames in the input file: " << fileName << "\n";
		return frameMarkerData;
	}

	std::auto_ptr<UuIcsC3d::C3dFile> inFilePointer = inFileInfo.open();
	
	for (uint i = 0; i < inFrameCount; ++i) 
	{
		UuIcsC3d::FrameData frameData;
		inFilePointer->get_frame_data(frameData, i);
		std::map<uint, Marker::MarkerData > frameMarkers;
		for(uint markerID = 0; markerID < frameData.points.size(); markerID++)
		{
			Marker::MarkerData marker;//(new Marker::MarkerData());
			marker.setPositionX(frameData.points[markerID].x());
			marker.setPositionY(frameData.points[markerID].y());
			marker.setPositionZ(frameData.points[markerID].z());
			
			frameMarkers.insert(std::make_pair(markerID, marker));
		}
		frameMarkerData.push_back(frameMarkers);
	}

	inFilePointer.reset();
	return frameMarkerData;
}