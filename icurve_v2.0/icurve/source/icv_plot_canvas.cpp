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


#define ICV_TOLERENCE_DISTANCE 5


IcvPlotCanvas::IcvPlotCanvas(QwtPlot *parent)
{
    plot = parent;
    canvas = static_cast<QwtPlotCanvas *>(plot->canvas());
    canvas->installEventFilter(this);
    canvas->setFocus();
    canvas->setCursor(Qt::ArrowCursor);
    canvas->setMouseTracking(true);

    selectedPlotItem = NULL;
}


IcvPlotCanvas::~IcvPlotCanvas()
{

}


QwtPlot *IcvPlotCanvas::getPlot()
{
    return plot;
}


#if 0
const QwtPlot *IcvPlotCanvas::getPlot() const
{
    return qobject_cast<const QwtPlot *>(parent());
}
#endif


QwtPlotCanvas* IcvPlotCanvas::getPlotCanvas()
{
    return canvas;
}


void IcvPlotCanvas::select(const QPoint &pos)
{
    const QwtPlotItemList &itmList = plot->itemList();

    /*pick the selected curve*/
    for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); it++)
    {
        if(QwtPlotItem::Rtti_PlotCurve == (*it)->rtti())
        {
            QwtPlotCurve *curve = static_cast<QwtPlotCurve*>(*it);
            double dist = 0.0;
            curve->closestPoint(pos, &dist);

            if(dist <= ICV_TOLERENCE_DISTANCE )
            {
                selectedPlotItem = *it;
                break;
            }
            else
            {
                selectedPlotItem = NULL;
            }
        }
    }

    if(NULL != canvas && plot != NULL)
    {

        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        plot->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }

    return ;
}


QwtPlotCurve* IcvPlotCanvas::getCurve()
{
    QwtPlotCurve *curveSel = NULL;
    QwtPlotItem *item = selectedPlotItem;

    if(NULL == item)
        return NULL;

    if( QwtPlotItem::Rtti_PlotCurve == item->rtti())
    {
        curveSel = static_cast<QwtPlotCurve *>(item);
    }

    return curveSel;
}


void IcvPlotCanvas::clearCurve()
{
    selectedPlotItem = NULL;
}


void IcvPlotCanvas::move(const QPoint &pos)
{
    const QwtPlotItemList &itmList = plot->itemList();

    for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); it++)
    {
        if( (*it)->rtti() == QwtPlotItem::Rtti_PlotCurve)
        {
            QwtPlotCurve *curveSel = static_cast<QwtPlotCurve *>(*it);
            double distance = 0.0;
            curveSel->closestPoint(pos,&distance);
            if(distance <= ICV_TOLERENCE_DISTANCE)
            {
                canvas->setCursor(Qt::PointingHandCursor);
                break;
            }
            else
            {
                canvas->setCursor(Qt::ArrowCursor);
            }
        }
    }
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
            select(mouseEventtt->pos());
            break;
        }

    case QEvent::MouseMove:
        {
            const QMouseEvent *mouseEventtt = static_cast<QMouseEvent*>(event);
            move(mouseEventtt->pos());
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


