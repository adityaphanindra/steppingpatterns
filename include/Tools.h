///
/// \file Tools.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>

///
/// \brief wrap radians to PI
/// \param input angle in radians
/// \return angle between (-pi, pi]
///
float wrapToPi(float input);

///
/// \brief wrap to PI
/// \param input angle in degrees
/// \return angle between (-180, 180]
///
float wrapTo180(float input);

///
/// \brief degree to radians
/// \param input angle in degrees
/// \return angle between (-pi, pi]
///
float degToRad(float input);

///
/// \brief radians to degree
/// \param input angle in radians
/// \return angle between (-180, 180]
///
float radToDeg(float input);

#endif