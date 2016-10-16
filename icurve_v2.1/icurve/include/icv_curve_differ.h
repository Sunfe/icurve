#ifndef ICV_CURVE_DIFFER_H
#define ICV_CURVE_DIFFER_H
#include <QDialog>
#include <QList>
#include "ui_icv_curve_differ.h"
#include "icv_icurve.h"
#include "icv_plot_curve.h"

class IcvPlotCurve;
class IcvCurveDiffer : public QDialog
{
    Q_OBJECT

public:
    IcvCurveDiffer(QList<IcvPlotCurve*> curves, QWidget *parent = 0);
    ~IcvCurveDiffer();

    void setWinMain(QWidget *icv);
    QWidget *mainWin();
    void setDiffCurves(QList<IcvPlotCurve*> crvs);
    void plotCurveDiff(IcvPlotCurve* cfirst, IcvPlotCurve*csecond);
public slots:
    void updatePlot(int index);
private:
    Ui::IcvCurveDiffer ui;
    QList<IcvPlotCurve*> curves;
    IcvPlotCurve* curveFist;
    IcvPlotCurve* curveSecond;
    QWidget *icvWin;
    /*Qwt objects*/	
    QwtPlot *plot;
    QwtPlotCurve *qwtCurve;
    QwtLegend *legend;
    QwtPlotLegendItem *legendItem;
    QwtPlotGrid *grid;
    QwtPlotMagnifier *magnifier;
    QwtPlotPicker *picker;
    QwtPlotPanner *panner;
    QwtPlotZoomer *zoomer;

};

#endif // ICV_CURVE_DIFFER_H
