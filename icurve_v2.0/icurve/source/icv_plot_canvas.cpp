/* qt header */
#include <qapplication.h>
#include <qevent.h>
#include <QtGlobal>
#include <QLine>
#include <QPolygonF>
#include <QMessageBox>
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

    createCurvePopMenus();
    createCurvePopMenuActions();

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


void IcvPlotCanvas::onMouseLeftButtonClick(const QPoint &pos)
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


void IcvPlotCanvas::onMouseRightButtonClick(const QPoint &pos)
{
    crvSelPopMenu->exec(pos);
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
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                onMouseLeftButtonClick(mouseEvent->pos());
            }
            else if(mouseEvent->button() == Qt::LeftButton)
            {

            }
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


void IcvPlotCanvas::createCurvePopMenus()
{

    crvSelPopMenu = new QMenu(this);
    crvSelPopMenu->addAction(delAction);
    crvSelPopMenu->addAction(colorSetAction);

    subCrvSelWidthMenu = new QMenu("width",this);
    subCrvSelWidthMenu->addActions(widthActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelWidthMenu);

    subCrvSelStyleMenu = new QMenu("style",this);
    subCrvSelStyleMenu->addActions(styleActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelStyleMenu);

    subCrvSelMarkeStyleMenu = new QMenu("Marker",this);
    subCrvSelMarkeStyleMenu->addActions(markerStyleActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelMarkeStyleMenu);

    subCrvSelMarkerSizeMenu = new QMenu("Marker size",this);
    subCrvSelMarkerSizeMenu->addActions(markerSizeActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelMarkerSizeMenu);

    crvSelPopMenu->addAction(propertySetAction);

}


void IcvPlotCanvas::createCurvePopMenuActions()
{
    QAction *action = NULL;

    /*delete the curve*/
    delAction = new QAction(QIcon(":/images/delete.png"),tr("Delete"),this);
    delAction->setShortcut(QKeySequence::Delete);
    delAction->setStatusTip("curve delete");
    connect(delAction,SIGNAL(triggered()),this,SLOT(delCurve()));

    /*color the curve*/
    colorSetAction = new QAction(tr("Color..."),this);
    colorSetAction->setStatusTip("curve set color");
    connect(colorSetAction,SIGNAL(triggered()),this,SLOT(setCurveColor()));

    /*{{{set width action*/
    widthActGrp = new QActionGroup(this);
    QString actionText;
    actionText = QString::number(0.5);
    action->setText(actionText);
    action->setData(0.5);
    for(qint8 i = 1; i< 11; i++)
    {
        actionText = QString::number(i);
        action->setText(actionText);
        action->setData(i);
    }
    connect(widthActGrp,SIGNAL(triggered(QAction *)),this,SLOT(setCurveWidth(QAction *)));

    /*{{{curve subCrvSelStyleMenu action*/
    QList < QPair<QString,int> > styleList;
    styleList.append(qMakePair(tr("Solid"),1));
    styleList.append(qMakePair(tr("Dash"),2));
    styleList.append(qMakePair(tr("Dot"),3));
    styleList.append(qMakePair(tr("DashDot"),4));
    styleList.append(qMakePair(tr("DashDotDot"),5));

    styleActGrp = new QActionGroup(this);
    for(qint16 i = 0; i < styleList.count(); i++)
    {
        action = new QAction(styleActGrp);
        action->setText((styleList.at(i).first));
        action->setData((styleList.at(i).second));

    }
    connect(styleActGrp,SIGNAL(triggered(QAction *)),this,SLOT(setCurveStyle(QAction *)));
    /*}}}*/

    /*{{{curve marker action*/
    QList< QPair<QString,int> > markerList;
    markerList.append(qMakePair(tr("None"),-1));
    markerList.append(qMakePair(tr("Ellipse"),0));
    markerList.append(qMakePair(tr("Rect"),1));
    markerList.append(qMakePair(tr("Diamond"),2));
    markerList.append(qMakePair(tr("Triangle"),3));
    markerList.append(qMakePair(tr("DTriangle"),4));
    markerList.append(qMakePair(tr("UTriangle"),5));
    markerList.append(qMakePair(tr("LTriangle"),6));
    markerList.append(qMakePair(tr("RTriangle"),7));
    markerList.append(qMakePair(tr("Cross(+)"),8));
    markerList.append(qMakePair(tr("XCross(x)"),9));
    markerList.append(qMakePair(tr("HLine"),10));
    markerList.append(qMakePair(tr("VLine"),11));
    markerList.append(qMakePair(tr("Star1"),12));
    markerList.append(qMakePair(tr("Star2"),13));
    markerList.append(qMakePair(tr("Hexagon"),14));

    markerStyleActGrp = new QActionGroup(this);
    QList <QPair<QString,int> >::iterator m;
    for(m = markerList.begin(); m < markerList.end(); m++)
    {
        action = new QAction(markerStyleActGrp);
        action->setText((m->first));
        action->setData((m->second));
    }
    connect(markerStyleActGrp,SIGNAL(triggered(QAction *)),this,SLOT(setCurveMarker(QAction *)));
    /*}}}*/


    /*{{{set curve marker size action*/
    QList< QPair<QString,int> > markerSize;
    markerSize.append(qMakePair(tr("2"),2));
    markerSize.append(qMakePair(tr("4"),4));
    markerSize.append(qMakePair(tr("5"),5));
    markerSize.append(qMakePair(tr("6"),6));
    markerSize.append(qMakePair(tr("7"),7));
    markerSize.append(qMakePair(tr("8"),8));
    markerSize.append(qMakePair(tr("10"),10));
    markerSize.append(qMakePair(tr("12"),12));
    markerSize.append(qMakePair(tr("18"),18));
    markerSize.append(qMakePair(tr("24"),24));
    markerSize.append(qMakePair(tr("48"),48));

    markerSizeActGrp = new QActionGroup(this);
    QList <QPair<QString,int> >::iterator t;
    for(t = markerSize.begin(); t < markerSize.end(); t++)
    {
        action = new QAction(markerSizeActGrp);
        action->setText((t->first));
        action->setData((t->second));
    }
    connect(markerSizeActGrp,SIGNAL(triggered(QAction *)),this,SLOT(setCurveMarkerSize(QAction *)));
    /*}}}*/


    propertySetAction = new QAction(tr("Properties..."),this);
    propertySetAction->setStatusTip("set curve properties");
    connect(propertySetAction,SIGNAL(triggered()),this,SLOT(setProperty()));

}


void IcvPlotCanvas::setCurveColor(IcvPlotCurve *curve)
{

    return  ;
}


void IcvPlotCanvas::seCurvetWidth(IcvPlotCurve *curve, QAction *action)
{
    return ;
}


void IcvPlotCanvas::setCurveStyle(IcvPlotCurve *curve, QAction *action)
{
    return ;
}


void IcvPlotCanvas::setCurveMarker(IcvPlotCurve *curve, QAction *action)
{
    return ;
}


void IcvPlotCanvas::setCurveMarkerSize(IcvPlotCurve *curve, QAction *action)
{
    return ;
}


void IcvPlotCanvas::setCurveProperty(IcvPlotCurve *curve)
{
    return ;
}
