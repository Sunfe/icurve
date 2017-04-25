#pragma once
#include "qwt_plot_picker.h"

class IcvPlotPicker : public QwtPlotPicker
{
public:
    explicit IcvPlotPicker( QWidget *canvas );
    explicit IcvPlotPicker(int xAxis, int yAxis, RubberBand rubberBand, 
        DisplayMode trackerMode, QWidget * wgt);
protected:
    virtual QwtText trackerTextF( const QPointF &pos ) const;
    ~IcvPlotPicker(void);
};
