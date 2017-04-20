#pragma once
#include "qwt_plot_zoomer.h"

class IcvPlotZoomer : public QwtPlotZoomer
{
public:
    IcvPlotZoomer( QWidget *canvas );
    ~IcvPlotZoomer(void);
};
