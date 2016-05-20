#ifndef CANVAS_PICKER_H
#define CANVAS_PICKER_H

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
class QLineF;
class QwtPlot;
class QPolygonF;
class QwtPlotCurve;


class CanvasPicker : public QObject
{
    Q_OBJECT

    public:
        CanvasPicker(QwtPlot *plot);
        virtual bool eventFilter( QObject *, QEvent * );
        virtual bool event( QEvent * );
        QwtPlotCurve * getCurve();
        void clearCurve();
        QVector<QwtPlotMarker *>* getMarker();
        void delMarker();

    private:
        void select(const QPoint &);
        void move(const QPoint &);
        QwtPlot *plot();
        const QwtPlot *plot() const;

    private:
        QwtPlotItem * itemSelect;
        QVector<QwtPlotMarker *> *curveMarker;

};

#endif
