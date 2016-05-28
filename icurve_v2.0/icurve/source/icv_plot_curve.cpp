/* qt header */
#include <qapplication.h>
#include <qevent.h>
#include <QtGlobal>
#include <QLine>
#include <QPolygonF>
#include <math.h>
/* qwt header */
#include <qwt_plot_directpainter.h>
/* app header */
#include "icv_plot_canvas.h"
#include "icv_plot_curve.h"


IcvPlotCurve::IcvPlotCurve(QwtPlotCurve *crv)
{
    curve  = crv;  
    canvas = NULL;
    plot   = NULL;
    setMarker();
    activateState = ICV_CURVE_UNACTIVATED;
}


IcvPlotCurve::IcvPlotCurve()
{
    curve  = NULL;
    plot   = NULL;
    canvas = NULL;
    activateState = ICV_CURVE_UNACTIVATED;
}


IcvPlotCurve::~IcvPlotCurve()
{

}


QwtPlot *IcvPlotCurve::getPlot()
{
    return plot;
}


void IcvPlotCurve::setPlot(QwtPlot *plt)
{
    plot = plt;
}


QwtPlotCanvas* IcvPlotCurve::getCanvas()
{
    return canvas;
}


void IcvPlotCurve::setCanvas(QwtPlotCanvas *cvs)
{
    canvas = cvs;
}


QwtPlotCurve * IcvPlotCurve::getCurve()
{
    return curve;
}


void IcvPlotCurve::setCurve(QwtPlotCurve *crv)
{
    curve = crv;
    setMarker();
}


qint16 IcvPlotCurve::getActivateState()
{
    return activateState;
}


void IcvPlotCurve::setActivateState(qint16 state)
{
    activateState = state;
}


QVector<QwtPlotMarker *> IcvPlotCurve::getMarkers()
{
    return markers;
}


void IcvPlotCurve::setMarker()
{
    if(NULL == curve)
        return ;

    qint16 sampleSize = curve->dataSize();
    qint16 step = 0;
    qint16 markerTotalCount = 0;

    if( sampleSize < ICV_CURVE_MAX_MARKER_NUM)
    {
        step = 1;
        markerTotalCount = sampleSize;
    }
    else
    {
        step = static_cast<qint16>(sampleSize/ICV_CURVE_MAX_MARKER_NUM);
        markerTotalCount = ICV_CURVE_MAX_MARKER_NUM;
    }

    qint16 samplePos = 0;
    for(qint16 cnt= 0; cnt < markerTotalCount; cnt++)
    {
        QwtPlotMarker *marker = new QwtPlotMarker();
        marker->setValue(curve->sample(samplePos).x(),
            curve->sample(samplePos).y());
        marker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom);
        marker->setLinePen(QPen( Qt::green, 0, Qt::DashDotLine));
        marker->setSymbol(new QwtSymbol( QwtSymbol::Ellipse ,
            QColor(curve->pen().color()), 
            QColor(curve->pen().color()), 
            QSize(4, 4)));
        markers.append(marker);
        samplePos += step;
    }

    return;
}


void IcvPlotCurve::showMarker()
{
    for(qint16 pos = 0; pos < markers.count(); pos++)
    {
        markers.at(pos)->attach(plot);
    }

    if(NULL != canvas && plot != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        plot->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }

    showMarkerState = ICV_CURVE_SHOW_MARKER;
    return;
}


void IcvPlotCurve::hideMarker()
{
    for(qint16 pos = 0; pos < markers.count(); pos++)
    {
        markers.at(pos)->detach();
    }

    if(NULL != canvas && plot != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        plot->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }

    showMarkerState = ICV_CURVE_HIDE_MARKER;
    return ;
}


qint16 IcvPlotCurve::getShowMarkerState()
{
    return showMarkerState;
}


void IcvPlotCurve::setShowMarkerState(qint16 state)
{
    showMarkerState = state;
}


void IcvPlotCurve::setColor(QColor color)
{
    QPen pen(color);
    QBrush brush(color);

    curve->setPen(pen);

    for(qint16 cnt= 0; cnt < markers.count(); cnt++)
    {
        const QwtSymbol *symbol = markers.value(cnt)->symbol();
        if(symbol != NULL)
        {
            QwtSymbol *symbolNew = new QwtSymbol(symbol->style(), brush, pen, symbol->size());
            markers.value(cnt)->setSymbol(symbolNew);
        }
    }

    return ;
}


void IcvPlotCurve::setWidth(qint16 width)
{
    QPen pen = curve->pen();
    pen.setWidth(width);
    curve->setPen(pen);

    return ;
}


void IcvPlotCurve::setStyle(Qt::PenStyle style)
{
    QPen pen = curve->pen();
    pen.setStyle(style);
    curve->setPen(pen);

    return ;
}


void IcvPlotCurve::setMarker(QwtSymbol::Style style)
{

    for(qint16 cnt= 0; cnt < markers.count(); cnt++)
    {
        const QwtSymbol *symbol = markers.value(cnt)->symbol();
        if(symbol != NULL)
        {
            QwtSymbol *symbolNew = new QwtSymbol(style, symbol->brush(),symbol->pen(),symbol->size());
            markers.value(cnt)->setSymbol(symbolNew);
        }
    }

    return ;
}


void IcvPlotCurve::setMarkerSize(qint16 size)
{

    for(qint16 cnt= 0; cnt < markers.count(); cnt++)
    {
        const QwtSymbol *symbol = markers.value(cnt)->symbol();
        if(symbol != NULL)
        {
            QwtSymbol *symbolNew = new QwtSymbol(symbol->style(), symbol->brush(),symbol->pen(),QSize(size,size));
            markers.value(cnt)->setSymbol(symbolNew);
        }
    }


    return ;
}