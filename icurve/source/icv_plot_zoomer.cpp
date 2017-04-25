#include "icv_plot_zoomer.h"

IcvPlotZoomer::IcvPlotZoomer(QWidget *canvas) : QwtPlotZoomer( canvas )
{
    setRubberBandPen( QColor( Qt::black ) );
    setRubberBand( QwtPicker::RectRubberBand );
    setTrackerMode( QwtPlotPicker::AlwaysOff );
    zoom(0);
    setEnabled(false);
}

IcvPlotZoomer::~IcvPlotZoomer(void)
{
}
