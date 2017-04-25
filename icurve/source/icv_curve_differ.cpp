#include <QStringList>
#include <iostream>     // std::cout  
#include <functional>   // std::minus  
#include <numeric>      // std::accumulate  
#include <iostream>     // std::cout
#include <vector>       // std::vector, std::begin, std::end
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include "icv_curve_differ.h"
#include "icv_icurve.h"
#include "icv_plot_curve.h"

IcvCurveDiffer::IcvCurveDiffer(QList<IcvPlotCurve*> curves, QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    qwtCurve = NULL;
    icvWin = parent;

    plot = new QwtPlot();
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, -150.0, 150.0 );
    plot->setAxisScale( QwtPlot::xBottom, 0, 3000 );
    plot->setAxisLabelAlignment(QwtPlot::xBottom,Qt::AlignLeft);
    plot->setAxisLabelAlignment(QwtPlot::yLeft,Qt::AlignTop);
    plot->plotLayout()->setAlignCanvasToScales( false );
    plot->plotLayout()->setCanvasMargin(0);
    plot->canvas()->setCursor(Qt::ArrowCursor);
    /* legendItem, default curve title is displayed */
    legendItem = new QwtPlotLegendItem();  
    legendItem->attach(plot);
    /* legend */
    legend = new QwtLegend;
    /* grid */
    grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::DashLine));
    grid->setMinorPen(QPen(Qt::DashLine));  
    grid->attach( plot );
    /* magnifier */
    magnifier = new QwtPlotMagnifier(plot->canvas());
    magnifier->setEnabled(true);
    /* panner */
    panner = new QwtPlotPanner(plot->canvas());
    panner->setEnabled(true);
    ui.horizontalLayout->addWidget(plot);
    connect(ui.comboBoxFirst,  SIGNAL(activated(int)), this, SLOT(updatePlot(int)));
    connect(ui.comboBoxSecond, SIGNAL(activated(int)), this, SLOT(updatePlot(int)));

    if(!curves.isEmpty())
    {
        curveFist = curves.at(0);
        curveSecond = curves.at(curves.count()-1);
        plotCurveDiff(curveFist, curveSecond);
    }
}


IcvCurveDiffer::~IcvCurveDiffer()
{

}


void IcvCurveDiffer::setWinMain(QWidget *icv)
{
    icvWin = icv;
}


QWidget* IcvCurveDiffer::mainWin()
{
    return icvWin;
}


void IcvCurveDiffer::updatePlot(int index)
{
    if((curves.count() == 0) || (index > curves.count()))
        return;

    if(sender() == ui.comboBoxFirst)
        curveFist = curves.at(index);
    else if(sender() == ui.comboBoxSecond)
        curveSecond = curves.at(curves.count()-1-index);
    if((NULL == curveFist) || (NULL == curveSecond))
        return;

    plotCurveDiff(curveFist, curveSecond);
    return;
}


void IcvCurveDiffer::setDiffCurves(QList<IcvPlotCurve*> crvs)
{
    curves = crvs;
    QStringList curveTitileFirst;
    for(qint16 cnt = 0; cnt < curves.count(); cnt++)
    {
        IcvCommand cmd = curves.at(cnt)->getCommand();
        QString name = cmd.getTitle() + "," + QString::number(cmd.getDataPosInFile());
        curveTitileFirst.append(name);     
    }

    QStringList curveTitileSecond;
    for(qint16 cnt = curves.count() - 1; cnt >= 0; cnt--)
    {
        IcvCommand cmd = curves.at(cnt)->getCommand();
        QString name = cmd.getTitle() + "," + QString::number(cmd.getDataPosInFile());
        curveTitileSecond.append(name);     
    }
    ui.comboBoxFirst->addItems(curveTitileFirst);
    ui.comboBoxSecond->addItems(curveTitileSecond);
    int idxf = ui.comboBoxFirst->currentIndex();
    if(idxf < 0 || idxf > crvs.count())
        return;
    int idxs = crvs.count()-1-ui.comboBoxSecond->currentIndex();
    if(idxs < 0 || idxs > crvs.count())
        return;
    plotCurveDiff(crvs.at(idxf), crvs.at(idxs));
    return;
}


void IcvCurveDiffer::plotCurveDiff(IcvPlotCurve* cfirst, IcvPlotCurve*csecond)
{
    if(NULL == cfirst || NULL == csecond)
        return;

    QList<QPointF> fp = cfirst->getCommand().getData();
    QList<QPointF> sp = csecond->getCommand().getData();
    QList<QPointF> diffp;
    qreal upperTone =  fp.count() < sp.count()? fp.count():sp.count();
    for(qint16 tone = 0; tone < upperTone; tone++)
    {
        QPointF point;
        point.setX(tone);
        point.setY(fp.at(tone).y() - sp.at(tone).y());
        diffp.append(point);
    }

    if(qwtCurve != NULL)
        delete qwtCurve;
    qwtCurve = new QwtPlotCurve();
    qwtCurve->setPen(Qt::red, 1.0, Qt::SolidLine);
    qwtCurve->setSamples(diffp.toVector());
    qwtCurve->setTitle("difference");
    qwtCurve->attach(plot);

    /* set to optimal plot view */
    QList<QPointF> data = diffp;
    std::vector<qreal> crvRx;
    std::vector<qreal> crvRy;
    for(qint16 count = 0; count < data.count(); count++)
    {
        crvRx.push_back(data.value(count).rx());
        crvRy.push_back(data.value(count).ry());
    }
    /* find minimum */
    double minRx = *std::min_element(crvRx.begin(), crvRx.end());
    double minRy = *std::min_element(crvRy.begin(), crvRy.end());
    /* find maximum */
    double maxRx = *std::max_element(crvRx.begin(), crvRx.end());
    double maxRy = *std::max_element(crvRy.begin(), crvRy.end());
     plot->setAxisScale(QwtPlot::xBottom, minRx - ICV_EYESCAN_MARGIN, maxRx + ICV_EYESCAN_MARGIN);
    plot->setAxisScale(QwtPlot::yLeft,    minRy - ICV_EYESCAN_MARGIN, maxRy + ICV_EYESCAN_MARGIN);
    plot->replot();
    return;
}

