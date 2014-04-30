///
/// \file MainUI.h
/// \brief 
/// \author PISUPATI Phanindra
/// \date 01.04.2014
///

#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <qgridlayout.h>
#include "qcustomplot.h"

///
/// \class VisualToolUI
/// \brief Main UI Class
///
class VisualToolUI : public QMainWindow
{
	Q_OBJECT	
private:
	QCustomPlot *			_plot; 			///< The plot

public:
	///
	/// \brief Constructor
	///
	VisualToolUI();

private:
	///
	/// \brief Creates an empty plot
	///
	void createPlot();
	
signals:
	
private slots:
};

#endif