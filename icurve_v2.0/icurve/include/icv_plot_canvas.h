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
    const QwtPlot *getPlot() const;

    QwtPlotCanvas *getPlotCanvas();


    QwtPlotCurve * getCurve();
    void clearCurve();

    virtual bool eventFilter( QObject *, QEvent * );
    virtual bool event( QEvent * );


private:
    void select(const QPoint &);
    void move(const QPoint &);

private:
    QwtPlot *plot;
    QwtPlotCanvas *canvas;
    QwtPlotItem *selectedPlotItem;

};

#endif
