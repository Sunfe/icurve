/* qt header */
#include <qapplication.h>
#include <qevent.h>
#include <QtGlobal>
#include <QLine>
#include <QPolygonF>
#include <math.h>
/* qwt header */
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_directpainter.h>
/* app header */
#include "icv_plot_canvas.h"


#define ICV_TOLERENCE_DISTANCE              (5)


IcvPlotCanvas::IcvPlotCanvas(QwtPlot *parent)
{
    plot = parent;
    canvas = static_cast<QwtPlotCanvas *>(plot->canvas());
    canvas->installEventFilter(this);
    canvas->setFocus();
    canvas->setCursor(Qt::ArrowCursor);
    canvas->setMouseTracking(true);

    updateCurves();

    curSelectedCurve  = NULL;
    prevSelectedCurve = NULL;
}


IcvPlotCanvas::~IcvPlotCanvas()
{

}


QwtPlot *IcvPlotCanvas::getPlot()
{
    return plot;
}


void IcvPlotCanvas::setPlot(QwtPlot *plt)
{
    plot = plt;
}


QwtPlotCanvas* IcvPlotCanvas::getPlotCanvas()
{
    return canvas;
}


void IcvPlotCanvas::setPlotCanvas()
{
    if(plot != NULL)
        canvas = static_cast<QwtPlotCanvas *>(plot->canvas());
    else
        canvas = NULL;
}


QList<IcvPlotCurve *> IcvPlotCanvas::getCurves()
{
    return curves;
}


void IcvPlotCanvas::setCurves(QList<IcvPlotCurve *> crvs)
{
    curves = crvs;
}


void IcvPlotCanvas::updateCurves()
{
    QwtPlotItemList items = plot->itemList();

    for(qint16 i = 0; i < items.count(); i++)
    {
        if((items.value(i))->rtti() == QwtPlotItem::Rtti_PlotCurve)
        {
            IcvPlotCurve *curve = new IcvPlotCurve();
            curve->setPlot(plot);
            curve->setCanvas(canvas);
            curve->setCurve(static_cast<QwtPlotCurve *>(items.value(i)));
            curves.append(curve);
        }
    }
}


void IcvPlotCanvas::lookforCurves()
{
    return updateCurves();
}


void IcvPlotCanvas::clearCurves()
{
    curves.clear();
}


IcvPlotCurve* IcvPlotCanvas::getSelectedCurve()
{
    return curSelectedCurve;
}


void IcvPlotCanvas::onMouseClick(const QPoint &pos)
{
    /*pick the selected curve*/
    for(qint16 i = 0; i < curves.count(); i++)
    {
        QwtPlotCurve *curve = curves.value(i)->getCurve();
        double dist         = 0.0;
        curve->closestPoint(pos, &dist);

        if(dist < ICV_TOLERENCE_DISTANCE )
        {
            curSelectedCurve = curves.value(i);
            break;
        }
        else
        {
            curSelectedCurve = NULL;
        }
    }
    
    /*Set markers*/
    if(NULL != curSelectedCurve)
    {
        curSelectedCurve->showMarker();
    }
    else if(NULL != prevSelectedCurve)
    {
        prevSelectedCurve->hideMarker();
    }

    prevSelectedCurve = curSelectedCurve;
    return ;
}


void IcvPlotCanvas::onMouseMove(const QPoint &pos)
{
   //lookforCurves();
    /*pick the selected curve*/
    for(qint16 i = 0; i < curves.count(); i++)
    {
        QwtPlotCurve *curve = curves.value(i)->getCurve();
        double dist        = 0.0;
        curve->closestPoint(pos, &dist);

        if(dist <= ICV_TOLERENCE_DISTANCE )
        {
            canvas->setCursor(Qt::PointingHandCursor);
            curves.value(i)->setActivateState(ICV_CURVE_ACTIVATED);
            curSelectedCurve = curves.value(i);
            break;
        }
        else
        {
            canvas->setCursor(Qt::ArrowCursor);
            curSelectedCurve  = NULL;
        }
    }

    return ;
}


bool IcvPlotCanvas::eventFilter(QObject *object, QEvent *event)
{

    if((NULL == plot)||(object != plot->canvas()))
        return false;

    switch(event->type())
    {
    case QEvent::MouseButtonPress:
        {
            const QMouseEvent *mouseEventtt = static_cast<QMouseEvent*>(event);
            onMouseClick(mouseEventtt->pos());
            break;
        }

    case QEvent::MouseMove:
        {
            const QMouseEvent *mouseEventtt = static_cast<QMouseEvent*>(event);
            onMouseMove(mouseEventtt->pos());
            break;
        }
    default:
        break;

    }

    return QObject::eventFilter(object,event);
}


bool IcvPlotCanvas::event(QEvent *eve)
{
    return QObject::event(eve);
}


