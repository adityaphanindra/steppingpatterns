///
/// \file StringFunc.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include <string>

using namespace std;

#ifndef STRINGFUNC_H
#define STRINGFUNC_H

#include <sstream>

///
/// \brief string to integer
/// \param input string
/// \return integer
///
int stringToInt(string input);

///
/// \brief string to unsigned int
/// \param input string
/// \return unsigned integer
///
unsigned int stringToUInt(string input);

///
/// \brief integer to string
/// \param input int
/// \return string
///
string intToString(int input);

#endif