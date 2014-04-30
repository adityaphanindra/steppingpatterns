///
/// \file MainUI.cpp
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#include "MainUI.h"

// --------------------------------------------------------- Constructors
VisualToolUI::VisualToolUI() : 
	QMainWindow() 
{
	_plot = new QCustomPlot(this);
	_plot->setMinimumSize(600, 600);

	QGridLayout * gridLayout = new QGridLayout();
	gridLayout->addWidget(_plot); // add plot to layout
	setLayout(gridLayout);
}