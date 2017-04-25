#include "qwt_picker_machine.h"
#include "icv_plot_picker.h"

IcvPlotPicker::IcvPlotPicker(int xAxis, int yAxis, RubberBand rubberBand, 
              DisplayMode trackerMode, QWidget * wgt) :
QwtPlotPicker(xAxis, yAxis, rubberBand, trackerMode, wgt)
{
}

IcvPlotPicker::IcvPlotPicker( QWidget *canvas ) : QwtPlotPicker( canvas )
{
    setRubberBandPen(QColor(Qt::red));
    setTrackerPen(QColor(Qt::blue));
    setStateMachine(new QwtPickerDragPointMachine());
    setRubberBand(QwtPicker::CrossRubberBand);
    setTrackerMode(QwtPlotPicker::AlwaysOn);
}
QwtText IcvPlotPicker::trackerTextF( const QPointF &pos ) const
{
    QString axis;
    axis.sprintf("%.0f, %.0f", pos.x(), pos.y());
    QwtText text(axis);
    text.setColor( Qt::black );
    text.setBorderPen(QPen(Qt::lightGray));
    text.setBackgroundBrush(Qt::lightGray);
    text.setBorderRadius(6);
    return text;
}

IcvPlotPicker::~IcvPlotPicker(void)
{
}