///
/// \file main.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include <iostream>
#include <qapplication.h>
#include "MainUI.h"

#define DEBUG 1

using namespace std;

int main(int argc, char ** argv) 
{
	QApplication app(argc, argv);
	VisualToolUI * ui = new VisualToolUI();
	ui->setMinimumSize(600, 600);
	ui->show();	
	

	if(DEBUG)
		cout << "main(): End of program!" << endl;
	return app.exec();
}