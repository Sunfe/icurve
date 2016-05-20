#include <QtGlobal>
#include <qapplication.h>
#include <qevent.h>
#include <qwt_plot_directpainter.h>
#include <qwt_plot_marker.h>
#include <QLine>
#include <QPolygonF>
#include "Canvaspicker.h"
#include <QMessageBox>
#include <math.h>

#define TOLERENCE_DISTANCE 10
#define MAX_MARKER_NUM 40

CanvasPicker::CanvasPicker(QwtPlot *plot) :
    QObject( plot )
{
    itemSelect = NULL;
    curveMarker = new QVector<QwtPlotMarker *>;
    QwtPlotCanvas *canvas = plot->canvas();
    canvas->installEventFilter(this);
    canvas->setFocus();
    canvas->setCursor(Qt::ArrowCursor);
    canvas->setMouseTracking(true);
}


QwtPlot *CanvasPicker::plot()
{
    return qobject_cast <QwtPlot * >(parent());
}

const QwtPlot *CanvasPicker::plot() const
{
    return qobject_cast<const QwtPlot *>( parent() );
}


bool CanvasPicker::event(QEvent *ev)
{
    return QObject::event(ev);

}

bool CanvasPicker::eventFilter(QObject *object, QEvent *event)
{

    if((NULL == plot())||(object!=plot()->canvas()))
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

void CanvasPicker::select(const QPoint &pos)
{
    QwtPlotCanvas *canvas = NULL;
    QVector<QwtPlotMarker *> *markers = NULL;
    QwtPlotMarker *marker = NULL;
    int markerNum = 0;
    const QwtPlotItemList &itmList = plot()->itemList();

    /*pick the selected curve*/
    for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); it++)
    {
        if(QwtPlotItem::Rtti_PlotCurve == (*it)->rtti())
        {
            QwtPlotCurve *curve = static_cast<QwtPlotCurve *>(*it);
            double dist = 0.0;
            curve->closestPoint(pos, &dist);

            if(dist <= TOLERENCE_DISTANCE )
            {
                itemSelect = *it;
                break;
            }
            else
            {
                itemSelect = NULL;
            }
        }
    }


    /*Set markers*/
    if(NULL == getCurve())
    {
        /*release resources occupied by curve marker */
        delMarker();
    }
    else
    {
        canvas = plot()->canvas();
        markers = getMarker();
        markerNum = markers->size();
        for(int i = 0; i < markerNum; i++)
        {
            marker = markers->at(i);
            marker->attach(plot());
        }
    }

    plot()->canvas()->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
    plot()->replot();
    plot()->canvas()->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);

}

void CanvasPicker::move(const QPoint &pos)
{
    QwtPlotCanvas *canvas = plot()->canvas();
    const QwtPlotItemList &itmList = plot()->itemList();

    for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); it++)
    {
        if( (*it)->rtti() == QwtPlotItem::Rtti_PlotCurve)
        {
            QwtPlotCurve *curveSel = static_cast<QwtPlotCurve *>(*it);
            double distance = 0.0;
            curveSel->closestPoint(pos,&distance);
            if(distance <= TOLERENCE_DISTANCE)
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


QwtPlotCurve* CanvasPicker::getCurve()
{
    QwtPlotCurve *curveSel = NULL;
    QwtPlotItem *item = itemSelect;

    if(NULL == item)
        return NULL;

    if( QwtPlotItem::Rtti_PlotCurve == item->rtti())
    {
        curveSel = static_cast<QwtPlotCurve *>(item);
    }

    return curveSel;
}

void CanvasPicker::clearCurve()
{
    itemSelect = NULL;
}

QVector<QwtPlotMarker *>* CanvasPicker::getMarker()
{
    if(NULL == getCurve())
        return NULL;

    QwtPlotCurve* selCurve = getCurve();
    qint16 curveSampleSize = selCurve->dataSize();
    qint16 step = 0;
    qint16 size = 0;
    qint16 i = 0;
    qint16 t = 0;


    if( curveSampleSize < MAX_MARKER_NUM)
    {
        step = 1;
        size = curveSampleSize;
    }
    else
    {
        step = static_cast<qint16>(curveSampleSize/MAX_MARKER_NUM);
        size = MAX_MARKER_NUM;
    }

    delMarker();
    i = 0;
    for(t = 0; t < size; t++)
    {
        QwtPlotMarker *marker = new QwtPlotMarker();
        marker->setValue(selCurve->sample(i).x(),selCurve->sample(i).y());
        marker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
        marker->setLinePen( QPen( Qt::green, 0, Qt::DashDotLine ) );
        marker->setSymbol( new QwtSymbol( QwtSymbol::Star1,                  \
                    QColor( selCurve->pen().color()), \
                    QColor( selCurve->pen().color()), QSize( 4, 4 )));
        curveMarker->append(marker);
        i += step;
    }

    return curveMarker;
}

void CanvasPicker::delMarker()
{
    /*in case there is no markers*/
    if(curveMarker->begin() == curveMarker->end())
        return;

    QwtPlotMarker *marker = NULL;
    int i = 0;
    int size = curveMarker->size();

    for( i = 0; i < size; i++)
    {
        /*release resouces grabbed by marker*/
        marker = curveMarker->at(i);
        marker->detach();
        delete marker;
    }

    /*remove item from vector*/
    curveMarker->clear();
}


