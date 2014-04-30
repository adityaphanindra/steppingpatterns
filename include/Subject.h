///
/// \file Subject.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Settings.h"
#include "StringFunc.h"

using namespace std;

///
/// \class Subject
/// \brief Subject Class
///
class Subject
{
	///
	/// \struct Thresholds for the subject
	/// 
	struct Thresholds 
	{
		float speedCutoff;				///< max speed allowed
        float rotSpeedCutoff;			///< max rotation speed allowed
        float stepSizeThreshold;		///< step size threshold (# frames)
		float speedThreshold;			///< speed threshold
        float rotSpeedThreshold;		///< rotation speed threshold

		Thresholds() : 
			speedCutoff(50),
			rotSpeedCutoff(0.02),
			stepSizeThreshold(50),
			speedThreshold(436.8 / FRAME_RATE),
			rotSpeedThreshold(0.008)
		{
		}
	};

	///
	/// \struct Calibration Correction
	/// 
	struct CalibrationCorrection 
	{
		float	deltaXPelvis;
		float	deltaYPelvis;
		float	deltaYLeftFoot;
		float	deltaYRightFoot;
		float	deltaPhiPelvis;
		float	deltaPhiLeftFoot;
		float	deltaPhiRightFoot;

		CalibrationCorrection() :
			deltaXPelvis(0.0),
			deltaYPelvis(0.0),
			deltaYLeftFoot(0.0),
			deltaYRightFoot(0.0),
			deltaPhiPelvis(0.0),
			deltaPhiLeftFoot(0.0),
			deltaPhiRightFoot(0.0)	
		{
		}
	};

private:
	uint					_subjectNumber; 			///< subject number
	string					_c3dDirectory;				///< c3d directory
	Thresholds				_thresholds;				///< thresholds
	CalibrationCorrection	_calibrationCorrection;		///< calibration correction

public:
	///
	/// \brief Constructor
	/// \param subjectNumber: subject number
	///
	Subject(uint subjectNumber);

	///
	/// \brief set the thresholds for the subject
	/// \param thresholds: thresholds to determine the steps
	///
	void setThresholds(Thresholds thresholds);

	///
	/// \brief read the calibration files and store the corrections
	///
	void calibrate();

	///
	/// \brief initialise sequences
	///

private:
};


#endif