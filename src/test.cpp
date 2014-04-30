///
/// \file test.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include <iostream>
#include "Tools.h"

using namespace std;

int main(int argc, char ** argv) 
{
	while(true)
	{
		float input;
		cin >> input;
		cout << endl << wrapToPi(input) << endl;
	}
}