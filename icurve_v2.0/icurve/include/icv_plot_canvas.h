#ifndef ICV_PLOT_CANVAS_H
#define ICV_PLOT_CANVAS_H

#include <qobject.h>
#include <QtGlobal>
#include <qwhatsthis.h>
#include <qpainter.h>
#include <qwt_plot.h>
#include <qwt_symbol.h>
#include <qwt_scale_map.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include "icv_plot_curve.h"
class QPoint;
class QPointF;
class QCustomEvent;
class QwtPlot;
class QPolygonF;
class QwtPlotCurve;


class IcvPlotCanvas : public QObject
{
    Q_OBJECT

public:
    IcvPlotCanvas(QwtPlot *plot);
    ~IcvPlotCanvas();

    QwtPlot *getPlot();
    void setPlot(QwtPlot *plt);

    QwtPlotCanvas *getPlotCanvas();
    void setPlotCanvas();

    QList<IcvPlotCurve *> getCurves();
    void setCurves(QList<IcvPlotCurve *> crvs);
    void updateCurves();
    void lookforCurves();
    void clearCurves();

    IcvPlotCurve* getSelectedCurve();

    virtual bool eventFilter( QObject *, QEvent * );
    virtual bool event( QEvent * );


private:
    void onMouseClick(const QPoint &);
    void onMouseMove(const QPoint &);

private:
    QwtPlot *plot;
    QwtPlotCanvas *canvas;
    IcvPlotCurve *curSelectedCurve;
    IcvPlotCurve *prevSelectedCurve;
    QList<IcvPlotCurve *> curves;
};

#endif
