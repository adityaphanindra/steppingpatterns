///
/// \file C3DReader.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef C3DREADER_H
#define C3DREADER_H

#include <vector>
#include <map>
#include <memory>

#include "Settings.h"
#include "MarkerData.h"
#include "uuc3d.hpp"
#include "basic_io.hpp"

namespace C3D
{
///
/// \class C3DReader
/// \brief Reading and writing of c3d files
///
class C3DReader 
{
	uint											_frameRate;		///< frame rate
	uint											_numMarkers;	///< # of markers in c3d file
	UuIcsC3d::C3dFileInfo *							_fileInfo;		///< file info

public:
	///
	/// \brief Constructor
	///	\param numMarkers: 
	///	\param frameRate:
	///
	C3DReader(uint numMarkers, uint frameRate);
public:
	///
	/// \brief write to a C3D file
	///	\param numMarkers: 
	///	\param frameRate:
	///
	void writeToC3D(std::string fileName, std::vector<UuIcsC3d::FrameData> data);
	
	///
	/// \brief Read all frames from a C3D file
	///	\param fileName:
	///	\return 
	///
	std::vector<std::map<uint, Marker::MarkerData > > readAllFrames(std::string fileName);
};

};

#endif