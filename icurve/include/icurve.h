#ifndef ICURVE_H
#define ICURVE_H

#include <QtGui/QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_engine.h>
#include <qwt_color_map.h>
#include <qwt_text.h>
#include <qwt_text_engine.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_legenditem.h>
#include <qwt_plot_grid.h>

#include "ui_icurve.h"

class icurve : public QMainWindow
{
	Q_OBJECT

public:
	icurve(QWidget *parent = 0, Qt::WFlags flags = 0);
	void initMainPlotter(QwtPlot *plot=0);
	void initMainWinStyle(QMainWindow *self);
	~icurve();

private:
	Ui::icurveClass ui;
	QwtPlot *plot;
	QwtPlotGrid *grid;
	QwtSymbol *symbol;
private:

};

#endif // ICURVE_H
