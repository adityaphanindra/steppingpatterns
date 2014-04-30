///
/// \file Settings.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef SETTINGS_H
#define SETTINGS_H

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef PI
#define PI 3.1415927
#endif

typedef unsigned int uint;

const uint				NUM_MARKERS = 19;				///< total number of markers
const uint				NUM_SUBJECTS = 20;				///< total number of subjects
const uint				NUM_SEQUENCES = 386;			///< total number of sequences
const uint				NUM_TARGETS = 359;				///< total number of sequences
const uint				NUM_SESSIONS = 4;				///< total number of sessions
const uint				FRAME_RATE = 480;				///< frames per second
const uint				NORMALISATION_HEIGHT = 1860;	///< height in mm

enum BodyParts {LEFT_FOOT, RIGHT_FOOT, PELVIS};
enum FootMarkers {FOOT_LEFT, FOOT_TOP, FOOT_RIGHT, FOOT_BOTTOM};
enum PelvisMarkers {PELVIS_LEFT, PELVIS_RIGHT};

#endif