/* qt header */
#include <qapplication.h>
#include <qevent.h>
#include <QtGlobal>
#include <QLine>
#include <QPolygonF>
#include <QMessageBox>
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
    setMarkers();
    activateState   = ICV_CURVE_UNACTIVATED;
    showMarkerState = ICV_CURVE_HIDE_MARKER;
}


IcvPlotCurve::IcvPlotCurve()
{
    curve  = NULL;
    canvas = NULL;
    activateState = ICV_CURVE_UNACTIVATED;
}


IcvPlotCurve::~IcvPlotCurve()
{
    if(curve !=NULL )
    {
        curve->detach();
        delete curve;
    }

    for(qint16 pos= 0; pos < markers.count(); pos++)
    {
        markers.at(pos)->detach();
        delete markers.value(pos);
    }

    markers.clear();
    curve  = NULL;
    canvas = NULL;
    activateState   = 0;
    showMarkerState = 0;
}


IcvPlotCanvas* IcvPlotCurve::getCanvas()
{
    return canvas;
}


void IcvPlotCurve::setCanvas(IcvPlotCanvas *cvs)
{
    canvas = cvs;
}


QwtPlotCurve* IcvPlotCurve::getCurve()
{
    return curve;
}


void IcvPlotCurve::setCurve(QwtPlotCurve *crv)
{
    curve = crv;
    setMarkers();

    return ;
}


qint16 IcvPlotCurve::getDataPos()
{
    return dataPosition;
}


void IcvPlotCurve::setDataPos(qint16 pos)
{
    dataPosition = pos;
    return ;
}


qint16 IcvPlotCurve::getActivateState()
{
    return activateState;
}


void IcvPlotCurve::setActivateState(qint16 state)
{
    activateState = state;
    return ;
}


void IcvPlotCurve::showCurve()
{
    if(curve != NULL)
    {
        curve->attach(canvas->getCanvas()->plot());
        showMarkers();
    }

    return;
}


void IcvPlotCurve::hideCurve()
{
    if(curve == NULL)
        return ;

    curve->detach();
    for(qint16 pos= 0; pos < markers.count(); pos++)
    {
        markers[pos]->detach();
    }

    return;
}


void IcvPlotCurve::deleteCurve()
{
    if(curve == NULL)
        return;

    curve->detach();
    delete curve;

    for(qint16 pos= 0; pos < markers.count(); pos++)
    {
        markers[pos]->detach();
        delete markers[pos];
    }
    markers.clear();
 
    return;
}


QList<QwtPlotMarker *> IcvPlotCurve::getMarkers()
{
    return markers;
}


void IcvPlotCurve::setMarkers()
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
        marker->setSymbol(new QwtSymbol( QwtSymbol::Ellipse,
            QColor(curve->pen().color()), 
            QColor(curve->pen().color()), 
            QSize(4, 4)));
        markers.append(marker);
        samplePos += step;
    }

    return;
}


void IcvPlotCurve::showMarkers()
{
    for(qint16 pos = 0; pos < markers.count(); pos++)
    {
        markers.at(pos)->attach(canvas->getCanvas()->plot());
    }

    showMarkerState = ICV_CURVE_SHOW_MARKER;

    return;
}


void IcvPlotCurve::hideMarkers()
{
    for(qint16 pos = 0; pos < markers.count(); pos++)
    {
        markers[pos]->detach();
    }

    showMarkerState = ICV_CURVE_HIDE_MARKER;

    return;
}


void IcvPlotCurve::deleteMakers()
{  
    for(qint16 pos= 0; pos < markers.count(); pos++)
    {
        markers[pos]->detach();
        delete markers[pos];
    }
    markers.clear();

    return;
}


void IcvPlotCurve::updateMakers()
{
    deleteMakers();  /* delete previous markers */
    setMarkers();    /* set new markers */
    
    return;
}


qint16 IcvPlotCurve::getShowMarkerState()
{
    return showMarkerState;
}


void IcvPlotCurve::setShowMarkerState(qint16 state)
{
    showMarkerState = state;

    return;
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
            QwtSymbol *symbolNew = new QwtSymbol(symbol->style(),
                brush, pen, symbol->size());
            markers.value(cnt)->setSymbol(symbolNew);
        }
    }

    return;
}


void IcvPlotCurve::setWidth(qint16 width)
{
    QPen pen = curve->pen();
    pen.setWidth(width);
    curve->setPen(pen);

    return;
}


void IcvPlotCurve::setStyle(Qt::PenStyle style)
{
    QPen pen = curve->pen();
    pen.setStyle(style);
    curve->setPen(pen);

    return;
}


void IcvPlotCurve::setMarker(QwtSymbol::Style style)
{
    for(qint16 cnt= 0; cnt < markers.count(); cnt++)
    {
        const QwtSymbol *symbol = markers.value(cnt)->symbol();
        if(symbol != NULL)
        {
            QwtSymbol *symbolNew = new QwtSymbol(style, 
                symbol->brush(),
                symbol->pen(),
                symbol->size());
            markers.value(cnt)->setSymbol(symbolNew);
        }
    }

    return;
}


void IcvPlotCurve::setMarkerSize(qint16 size)
{
    for(qint16 cnt= 0; cnt < markers.count(); cnt++)
    {
        const QwtSymbol *symbol = markers.value(cnt)->symbol();
        if(symbol != NULL)
        {
            QwtSymbol *symbolNew = new QwtSymbol(symbol->style(), 
                symbol->brush(),
                symbol->pen(),
                QSize(size,size));
            markers.value(cnt)->setSymbol(symbolNew);
        }
    }

    return;
}


void IcvPlotCurve::setMarkerColor(QBrush brush, QPen pen)
{
    for(qint16 cnt= 0; cnt < markers.count(); cnt++)
    {
        const QwtSymbol *symbol = markers.value(cnt)->symbol();
        if(symbol != NULL)
        {
            QwtSymbol *symbolNew = new QwtSymbol(symbol->style(), 
                brush, pen, symbol->size());
            markers.value(cnt)->setSymbol(symbolNew);
        }
    }

    return;
}


void IcvPlotCurve::setGroupSize(qint16 size)
{
    if(NULL == canvas)
        return;

    IcvCommand cmd = canvas->retrieveParent()->getPlotData()->at(dataPosition);
    QList<QPointF> dataExpand;

    for(qint16 cnt = 0; cnt < cmd.getData().count(); cnt++)
    {
        for(qint16 si = 0; si < size; si++)
        {
            QPointF sample ;
            sample.setX(cnt * size + si );
            sample.setY(cmd.getData().at(cnt).y());
            dataExpand.append(sample);
        }
    }

    curve->setSamples(dataExpand.toVector());
    updateMakers();

    return;
}


void IcvPlotCurve::boldTitle(bool enable)
{
    if(curve == NULL)
        return;

    QwtText titleCur = curve->title();
    QFont font = titleCur.font();
    if(enable)
    {
        font.setWeight(QFont::Bold);
        font.setStyle(QFont::StyleItalic);
        titleCur.setFont(font);
    }
    else
    {
        font.setWeight(QFont::Normal);
        font.setStyle(QFont::StyleNormal);
        titleCur.setFont(font);
    }

    curve->setTitle(titleCur);
    return;
}


void IcvPlotCurve::setCommand(IcvCommand cmd)
{
    command = cmd;
    return;
}

IcvCommand IcvPlotCurve::getCommand()
{
    return command;
}

