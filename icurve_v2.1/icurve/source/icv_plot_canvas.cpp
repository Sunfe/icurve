#include <qapplication.h>
#include <qevent.h>
#include <Qt>
#include <QtGlobal>
#include <QLine>
#include <QPolygonF>
#include <QMessageBox>
#include <QColorDialog>
#include <math.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_directpainter.h>
#include <qwt_plot_zoomer.h>
#include "icv_plot_canvas.h"
#include "icv_curve_property.h"

#define ICV_TOLERENCE_DISTANCE              (5)

IcvPlotCanvas::IcvPlotCanvas(IcvICurve *parent)
{
    if(NULL == parent )
        return ;
    mainWin = parent;
    lockCursorMoveAction = false;

    canvas = static_cast<QwtPlotCanvas *>(parent->getPlot()->canvas());
    canvas->installEventFilter(this);
    canvas->setFocus();
    canvas->setCursor(Qt::ArrowCursor);
    canvas->setMouseTracking(true);
    initCurves();
}

IcvPlotCanvas::~IcvPlotCanvas()
{

}

IcvICurve* IcvPlotCanvas::retrieveParent()
{
    return mainWin;
}

QwtPlotCanvas* IcvPlotCanvas::getCanvas()
{
    return canvas;
}

void IcvPlotCanvas::setCanvas(QwtPlotCanvas * cvs)
{
    canvas = cvs;
    return;
}

QCursor IcvPlotCanvas::getCursor()
{
    return cursor;
}

void IcvPlotCanvas::setCursor(QCursor csr)
{
    cursor = csr;
    return;
}

void IcvPlotCanvas::restoreCursor()
{
    canvas->setCursor(cursor);
    return;
}

QList<IcvPlotCurve *> IcvPlotCanvas::getCurves()
{
    return curves;
}

void IcvPlotCanvas::setCurves(QList<IcvPlotCurve *> crvs)
{
    curves = crvs;
    return ;
}

void IcvPlotCanvas::setCurSelectCurves(QList<IcvPlotCurve *> crvs)
{
    curSelectedCurve = crvs ;
    return;
}

void IcvPlotCanvas::initCurves()
{
    return updateCurves();
}

void IcvPlotCanvas::updateCurves()
{
    QwtPlot *plot = canvas->plot();
    QwtPlotItemList items = plot->itemList();
    for(qint16 i = 0; i < items.count(); i++)
    {
        if((items.value(i))->rtti() == QwtPlotItem::Rtti_PlotCurve)
        {
            IcvPlotCurve *curve = new IcvPlotCurve();
            curve->setCurve(static_cast<QwtPlotCurve *>(items.value(i)));
            curve->setCanvas(this);
            curves.append(curve);
        }
    }
    return;
}

void IcvPlotCanvas::lookforCurves()
{
    return updateCurves();
}

void IcvPlotCanvas::appendCurves(IcvPlotCurve *curve)
{
    curves.append(curve);
    return;
}

void IcvPlotCanvas::clearCurves(QList<IcvPlotCurve *> crvs)
{
    for(qint16 pos = 0; pos < crvs.count(); pos++)
    {
        delete crvs[pos]; 
        curves.removeAll(crvs[pos]);     
        crvs[pos] = NULL;
    }
    return ;
}

void IcvPlotCanvas::removeSelectCurves()
{
    for(qint16 pos = 0; pos < curSelectedCurve.count(); pos++)
        prevSelectedCurve.removeAll(curSelectedCurve[pos]);     

    removeCurves(curSelectedCurve);
    return ;
}

void IcvPlotCanvas::hideSelectCurves()
{
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curSelectedCurve.at(cnt)->hideCurve();
    }
    return ;
}

void IcvPlotCanvas::showSelectCurves()
{
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curSelectedCurve.at(cnt)->showCurve();
    }
    return ;
}

void IcvPlotCanvas::clearAllCurves()
{
    for(qint16 pos = 0; pos < curves.count(); pos++)
    {
        delete curves[pos]; 
    }
    curves.clear();
    return;
}

void IcvPlotCanvas::deleteSelectCurve()
{
    lockMagnifier();
    if(0 == curSelectedCurve.count())
        return;
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
        "Curve will be deleted permanently, are you sure to proceeding?", 0, mainWin);
    msgBox.addButton(tr("Yes"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("No"),  QMessageBox::RejectRole);
    if (msgBox.exec() != QMessageBox::AcceptRole)
    {
        return;
    }
    /*remove from the curves' queue*/
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curves.removeAll(curSelectedCurve[cnt]); 

        /*remove relative data from QList data repository*/
        QList <IcvCommand> *plotData = retrieveParent()->getPlotData();
        qint16 dataPos = curSelectedCurve[cnt]->getDataPos();
        if(dataPos < plotData->count())
            plotData->removeAt(dataPos);
        /*update previous selected curves state*/
        prevSelectedCurve.removeAll(curSelectedCurve[cnt]);
        /*deconstruct IcvPlotCurve object */
        delete curSelectedCurve[cnt];       
        /*memset,important!*/
        curSelectedCurve[cnt] = NULL; 
    }
    if(canvas !=NULL && canvas->plot() != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        canvas->plot()->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }
    return;
}

void IcvPlotCanvas::deleteCurves(QList<IcvPlotCurve *> crv)
{
    if(crv.isEmpty())
        return;
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
        "Curve will be deleted permanently, are you sure to proceeding?", 0, mainWin);
    msgBox.addButton(tr("Yes"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("No"),  QMessageBox::RejectRole);
    if (msgBox.exec() != QMessageBox::AcceptRole)
    {
        return;
    }

    qint16 maxCnt = crv.count();
    QProgressDialog *progress =  retrieveParent()->createIcvProgressDiag(canvas->plot(), 0, maxCnt, 
        "progress", "deleting...", QSize(300,100), true);
    progress->show();
    for(qint16 cnt = 0; cnt < crv.count(); cnt++)
    {
        QwtPlotCurve *qwtCurve = crv[cnt]->getCurve();
        if(NULL == qwtCurve)
            continue;
        /*delete from qwtcavas*/
        qwtCurve->detach();
        /*delete from heap*/
        delete qwtCurve;  
        /*remove corresponding data from data repository*/
        QList <IcvCommand> *plotData = retrieveParent()->getPlotData();
        IcvCommand cmd = crv[cnt]->getCommand();
        for(QList<IcvCommand>::iterator iter = plotData->begin(); iter != plotData->end(); iter++)
        {
            if(*iter == cmd)
              plotData->erase(iter);
        }
        /*remove from list of curves in the IcvCanvas  */
        curves.removeAll(crv[cnt]);  
        /*detete corresponding markers*/
        crv[cnt]->deleteMakers();
        /*detete corresponding indicators*/
        crv[cnt]->deleteIndicator();
        /*update selected curve state*/
        curSelectedCurve.removeAll(crv[cnt]);
        prevSelectedCurve.removeAll(crv[cnt]);

        progress->setValue(cnt);
        if(0 == cnt %50)
            retrieveParent()->taskDelay(50);
    }
    delete progress;
    return;
}

void IcvPlotCanvas::removeCurves(QList<IcvPlotCurve *> crv)
{
    if(0 == crv.count())
        return ;

    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"), "Really to proceeding?", 0, this);
    msgBox.addButton(tr("Yes"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("No"),  QMessageBox::RejectRole);
    if (msgBox.exec() != QMessageBox::AcceptRole)
        return;

    qint16 maxCnt = crv.count();
    QProgressDialog *progress =  retrieveParent()->createIcvProgressDiag(canvas->plot(), 0, maxCnt, 
        "progress", "removing...", QSize(300,100), true);
    progress->show();

    for(qint16 cnt = 0; cnt < crv.count(); cnt++)
    {
        /*remove curve from canvas*/
        crv.at(cnt)->removeCurve();
        /*update selected curve state*/
        curSelectedCurve.removeAll(crv[cnt]);
        prevSelectedCurve.removeAll(crv[cnt]);
        progress->setValue(cnt);
        if(0 == cnt %50)
            retrieveParent()->taskDelay(50);
    }
    delete progress;
    return;
}

void IcvPlotCanvas::highlightCurve(QList<IcvPlotCurve *> crv)
{
    if(0 == crv.count())
        return;
    qint16 maxCnt = crv.count();
    for(qint16 cnt = 0; cnt < maxCnt; cnt++)
    {
        crv.at(cnt)->showMarkers();
        crv.at(cnt)->setActivateState(ICV_CURVE_ACTIVATED);
        if(0 == cnt%50)
            retrieveParent()->taskDelay(50);
    }
    if(NULL != canvas && canvas->plot() != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        canvas->plot()->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }
    return;
}

QList<IcvPlotCurve*> IcvPlotCanvas::getSelectedCurve()
{
    return curSelectedCurve;
}

QList<IcvPlotCurve *> IcvPlotCanvas::getCanvasCurves()
{
    canvasCurves.clear();
    for(qint16 i = 0; i < curves.count(); i++)
    {
        if(!curves[i]->isAttached())
            continue;
        canvasCurves.push_back(curves.at(i));
    }
    return canvasCurves;
}

void IcvPlotCanvas::setCurveColor()
{
    lockMagnifier();
    QColor color = QColorDialog::getColor(Qt::white,this);
    if(!color.isValid())
        return;
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curSelectedCurve[cnt]->setColor(color);
    }
    if(NULL != canvas && canvas->plot() != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        canvas->plot()->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }
    return;
}

void IcvPlotCanvas::setCurveWidth(QAction *action)
{
    lockMagnifier();
    if(NULL == action)
        return;
    bool ok;
    qint16 width = action->data().toInt(&ok);
    if(!ok)
        return ;
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curSelectedCurve[cnt]->setWidth(width);
    }
    if(NULL != canvas && canvas->plot() != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        canvas->plot()->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }

    action->setCheckable(true);
    action->setChecked(true);
    return;
}

void IcvPlotCanvas::setCurveStyle(QAction *action)
{
    lockMagnifier();
    if(NULL == action)
        return;
    bool ok;
    Qt::PenStyle style = static_cast<Qt::PenStyle>(action->data().toInt(&ok));
    if(!ok)
        return;
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curSelectedCurve.at(cnt)->setStyle(style);
    }
    if(NULL != canvas && canvas->plot() != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        canvas->plot()->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }

    action->setCheckable(true);
    action->setChecked(true);
    return;
}

void IcvPlotCanvas::setCurveMarker(QAction *action)
{
    lockMagnifier();
    if(NULL == action)
        return;
    bool ok;
    QwtSymbol::Style symStyle = static_cast<QwtSymbol::Style>(action->data().toInt(&ok));
    if(!ok)
        return;
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curSelectedCurve[cnt]->setMarker(symStyle);
    }
    if(NULL != canvas && canvas->plot() != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        canvas->plot()->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }

    action->setCheckable(true);
    action->setChecked(true);
    return;
}

void IcvPlotCanvas::setCurveMarkerSize(QAction *action)
{
    lockMagnifier();
    if(NULL == action)
        return;
    bool ok;
    qint16 size = action->data().toInt(&ok);
    if(!ok)
        return;
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curSelectedCurve[cnt]->setMarkerSize(size);
    }
    if(NULL != canvas && canvas->plot() != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        canvas->plot()->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }

    action->setCheckable(true);
    action->setChecked(true);
    return;
}

void IcvPlotCanvas::setCurveGroupSize(QAction *action)
{
    lockMagnifier();
    if(NULL == action)
        return;
    bool isConvertSuccess;
    qint16 size = action->data().toInt(&isConvertSuccess);
    if(!isConvertSuccess)
        return;
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        curSelectedCurve[cnt]->setGroupSize(size);
    }
    if(NULL != canvas && canvas->plot() != NULL)
    {
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
        canvas->plot()->replot();
        canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    }

    action->setCheckable(true);
    action->setChecked(true);
    return;
}

void IcvPlotCanvas::setCurveProperty()
{
    lockMagnifier();
    if(NULL == propertySetAction)
        return ;
    IcvCurvePropertyDialog *propDiag = new IcvCurvePropertyDialog(curSelectedCurve, mainWin, Qt::Dialog);
    propDiag->resize(400,150);
    propDiag->exec();
    return;
}

void IcvPlotCanvas::lockMagnifier()
{
    if(NULL != mainWin)
        mainWin->getMagnifier()->setEnabled(false);
    return;
}

void IcvPlotCanvas::unlockMagnifier()
{
    if(NULL != mainWin)
        mainWin->getMagnifier()->setEnabled(true);
    return;
}

void IcvPlotCanvas::setZoomState(bool state)
{
    zoomStateEnabled = state;
    return;
}

void IcvPlotCanvas::createCurvePopMenu()
{
    QWidget * parent  = this;
    crvSelPopMenu = new QMenu(parent);
    crvSelPopMenu->addAction(rmvAction);
    crvSelPopMenu->addAction(delAction);
    crvSelPopMenu->addAction(colorSetAction);

    subCrvSelWidthMenu = new QMenu("Width",parent);
    subCrvSelWidthMenu->addActions(widthActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelWidthMenu);

    subCrvSelStyleMenu = new QMenu("Style",this);
    subCrvSelStyleMenu->addActions(styleActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelStyleMenu);

    subCrvSelMarkeStyleMenu = new QMenu("Marker",parent);
    subCrvSelMarkeStyleMenu->addActions(markerStyleActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelMarkeStyleMenu);

    subCrvSelMarkerSizeMenu = new QMenu("Marker size",parent);
    subCrvSelMarkerSizeMenu->addActions(markerSizeActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelMarkerSizeMenu);

    subCrvSelGroupSizeMenu = new QMenu("Group size",parent);
    subCrvSelGroupSizeMenu->addActions(groupSizeActGrp->actions());
    crvSelPopMenu->addMenu(subCrvSelGroupSizeMenu);

    crvSelPopMenu->addAction(propertySetAction);
    return;
}

void IcvPlotCanvas::createCurvePopMenuAction()
{
    QWidget * parent  = this;
    QAction *action = NULL;
    /* remove the curve */
    rmvAction = new QAction(QIcon(":/images/remove.png"),tr("Remove"),parent);
    rmvAction->setShortcut(QKeySequence::Delete);
    rmvAction->setStatusTip("curve remove");
    connect(rmvAction, SIGNAL(triggered()),this,SLOT(removeSelectCurves()));
    /* delete the curve */
    delAction = new QAction(QIcon(":/images/delete.png"),tr("Delete"),parent);
    delAction->setShortcut(Qt::CTRL + Qt::Key_Delete);
    delAction->setStatusTip("curve delete");
    connect(delAction,SIGNAL(triggered()),this,SLOT(deleteSelectCurve()));
    /*color the curve*/
    colorSetAction = new QAction(tr("Color..."),parent);
    colorSetAction->setStatusTip("curve set color");
    connect(colorSetAction,SIGNAL(triggered()),this,SLOT(setCurveColor()));

    /*{{{set width action*/
    widthActGrp = new QActionGroup(parent);
    action      = new QAction(widthActGrp);
    action->setText(QString::number(0.5));
    action->setData(0.5);
    for(qint8 i = 1; i< 11; i++)  
    {
        action = new QAction(widthActGrp);
        action->setText(QString::number(i));
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
    styleActGrp = new QActionGroup(parent);
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
    markerStyleActGrp = new QActionGroup(parent);
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
    markerSizeActGrp = new QActionGroup(parent);
    QList <QPair<QString,int> >::iterator t;
    for(t = markerSize.begin(); t < markerSize.end(); t++)
    {
        action = new QAction(markerSizeActGrp);
        action->setText((t->first));
        action->setData((t->second));
    }
    connect(markerSizeActGrp,SIGNAL(triggered(QAction *)),this,SLOT(setCurveMarkerSize(QAction *)));
    /*}}}*/

    /*{{{set curve group size, to expand curve*/
    QList< QPair<QString,int> > groupSize;
    groupSize.append(qMakePair(tr("1"),  1));
    groupSize.append(qMakePair(tr("2"),  2));
    groupSize.append(qMakePair(tr("4"),  4));
    groupSize.append(qMakePair(tr("6"),  6));
    groupSize.append(qMakePair(tr("8"),  8));
    groupSize.append(qMakePair(tr("10"), 10));
    groupSize.append(qMakePair(tr("12"), 12));
    groupSize.append(qMakePair(tr("14"), 14));
    groupSize.append(qMakePair(tr("16"), 16));
    groupSizeActGrp = new QActionGroup(parent);
    QList <QPair<QString,int> >::iterator gsize;
    for(gsize = groupSize.begin(); gsize < groupSize.end(); gsize++)
    {
        action = new QAction(groupSizeActGrp);
        action->setText((gsize->first));
        action->setData((gsize->second));
    }
    connect(groupSizeActGrp, SIGNAL(triggered(QAction *)),this,SLOT(setCurveGroupSize(QAction *)));

    propertySetAction = new QAction(tr("Properties..."),this);
    propertySetAction->setStatusTip("set curve properties");
    connect(propertySetAction,SIGNAL(triggered()),this,SLOT(setCurveProperty()));
    return;
}

void IcvPlotCanvas::onMouseLeftButtonClick(const QMouseEvent *event, bool isCtrlPress)
{
    if(true == mainWin->isHandMoveChecked())
        return;
    /*release magnifier*/
    unlockMagnifier();
    if(!isCtrlPress)
    {
        /*hide previous seleced curve marker*/
        for(qint16 cnt = 0; cnt < prevSelectedCurve.count(); cnt++)
        {
            if(NULL == prevSelectedCurve[cnt])
                continue;
            prevSelectedCurve[cnt]->hideMarkers();
            prevSelectedCurve[cnt]->boldTitle(false);
        }
    }
    /*try to retrieve the closest curves*/
    const QPoint pos = event->pos();
    qint16 cntCurveSelected = 0;
    if(!isCtrlPress)
        curSelectedCurve.clear();
    for(qint16 i = 0; i < curves.count(); i++)
    {
        if(!curves[i]->isAttached())
            continue;
        QwtPlotCurve *curve = curves[i]->getCurve();
        double dist         = 0.0;
        curve->closestPoint(pos, &dist);
        if(dist < ICV_TOLERENCE_DISTANCE )
        {
            curSelectedCurve.push_back(curves[i]);
            cntCurveSelected++;
        }
    }
    /*show current selected curve markers*/
    QList<IcvPlotCurve *> allCurve = curves;
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        if(NULL == curSelectedCurve[cnt])
            continue;
        if(curSelectedCurve[cnt]->isAttached() == true)
        {
            curSelectedCurve[cnt]->showMarkers();
            curSelectedCurve[cnt]->boldTitle(true);
            allCurve.removeAll(curSelectedCurve[cnt]);
        }
    }
    /* the left curves were the unselected curves */
    for(qint16 cnt = 0; cnt < allCurve.count(); cnt++)
    {
        if(NULL == allCurve[cnt])
            continue;
        allCurve[cnt]->hideMarkers();
        allCurve[cnt]->boldTitle(false);
    }
    if(curSelectedCurve.isEmpty())
        lockCursorMoveAction = false;
    else
        lockCursorMoveAction = true;
    /* update previously selected curves */
    if(!isCtrlPress)
        prevSelectedCurve.clear();
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
        prevSelectedCurve.append(curSelectedCurve[cnt]);

    /*update replot*/
    canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
    canvas->plot()->replot();
    canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);

    QString statusInfo;
    statusInfo = QString::number(curSelectedCurve.count()) + " selected.";
    retrieveParent()->statusBar()->showMessage(statusInfo);
    return ;
}


void IcvPlotCanvas::onMouseRightButtonClick(const QMouseEvent * event)
{
    QwtPlotZoomer *zoomer = mainWin->getZoomer();
    if(zoomer->isEnabled())
        return ;
    lockMagnifier();
    lockCursorMoveAction = false;
    /*hide previous seleced curve marker*/
    for(qint16 cnt = 0; cnt < prevSelectedCurve.count(); cnt++)
    {
        if(NULL == prevSelectedCurve[cnt])
            continue;
        prevSelectedCurve[cnt]->hideMarkers();
    }
    /*try to retrieve the closest curves*/
    curSelectedCurve.clear();
    const QPoint pos = event->pos();
    qint16 cntCurveSelected = 0;
    for(qint16 i = 0; i < curves.count(); i++)
    {
        if(!curves[i]->isAttached())
            continue;
        QwtPlotCurve *curve = curves[i]->getCurve();
        double dist         = 0.0;
        curve->closestPoint(pos, &dist);
        if(dist < ICV_TOLERENCE_DISTANCE )
        {
            curSelectedCurve.push_back(curves[i]);
            cntCurveSelected++;
        }
    }
    /*show current selected curve markers*/
    QList<IcvPlotCurve *> allCurve = curves;
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
    {
        if(NULL == curSelectedCurve[cnt])
            continue;
        if(curSelectedCurve[cnt]->isAttached() == true)
        {
            curSelectedCurve[cnt]->showMarkers();
            curSelectedCurve[cnt]->boldTitle(true);
            allCurve.removeAll(curSelectedCurve[cnt]);
        }
    }
    /* the left curves were the unselected curves */
    for(qint16 cnt = 0; cnt < allCurve.count(); cnt++)
    {
        if(NULL == allCurve[cnt])
            continue;
        allCurve[cnt]->hideMarkers();
        allCurve[cnt]->boldTitle(false);
    }
    /*popup menu*/
    if(!curSelectedCurve.isEmpty())
        crvSelPopMenu->exec(event->globalPos());
    /* update previously selected curves */
    prevSelectedCurve.clear();
    for(qint16 cnt = 0; cnt < curSelectedCurve.count(); cnt++)
        prevSelectedCurve.append(curSelectedCurve[cnt]);
    /*update replot*/
    canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
    canvas->plot()->replot();
    canvas->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    QString statusInfo;
    statusInfo = QString::number(curSelectedCurve.count()) + " selected.";
    retrieveParent()->statusBar()->showMessage(statusInfo);
    return;
}

void IcvPlotCanvas::onMouseMove(const QMouseEvent * event)
{
    retrieveParent()->updateStatusBar();
    return;
    /* stop operation below */
    if(mainWin->isHandMoveChecked())
    {
        retrieveParent()->updateStatusBar();
        return;
    }
    QwtPlotZoomer *zoomer = mainWin->getZoomer();
    if(zoomer->isEnabled())
    {
        retrieveParent()->updateStatusBar();
        return;
    }
    if(true == lockCursorMoveAction)
    {
        retrieveParent()->updateStatusBar();
        return;
    }
    if(curves.isEmpty())
    {
        canvas->setCursor(Qt::ArrowCursor);
        retrieveParent()->updateStatusBar();
        return;
    }
    /* pick the selected curve */
    const QPoint pos = event->pos();
    for(qint16 i = 0; i < curves.count(); i++)
    {
        QwtPlotCurve *curve = curves[i]->getCurve();
        double dist        = 0.0;
        curve->closestPoint(pos, &dist);

        if(dist <= ICV_TOLERENCE_DISTANCE )
        {
            canvas->setCursor(Qt::PointingHandCursor);
            curves[i]->setActivateState(ICV_CURVE_ACTIVATED);
            break;
        }
        else
        {
            canvas->setCursor(Qt::ArrowCursor);
        }
    }
    retrieveParent()->updateStatusBar();
    return;
}

bool IcvPlotCanvas::eventFilter(QObject *object, QEvent *event)
{
    if((NULL == object) || (NULL == event) || (object != canvas))
        return false;
    switch(event->type())
    {
    case QEvent::MouseButtonPress:
        {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                onMouseLeftButtonClick(mouseEvent, (QApplication::keyboardModifiers() == Qt::ControlModifier)? true:false);
            }
            else if(mouseEvent->button() == Qt::RightButton)
            {
                onMouseRightButtonClick(mouseEvent);
            }
            break;
        }

    case QEvent::MouseMove:
        {
            const QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            onMouseMove(mouseEvent);
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

