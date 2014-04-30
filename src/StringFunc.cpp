///
/// \file StringFunc.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "StringFunc.h"

int stringToInt(string input)
{
	int output;
	istringstream ss;
	ss >> output;
	return output;
}

unsigned int stringToUInt(string input)
{
	unsigned int output;
	istringstream ss;
	ss >> output;
	return output;
}

string intToString(int input)
{
	string output;
	ostringstream ss;
	ss << output;
	return output;
}