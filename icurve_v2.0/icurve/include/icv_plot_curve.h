#ifndef ICV_CURVE_H
#define ICV_CURVE_H

#include <qobject.h>
#include <QtGlobal>
#include <QVector>
#include <QColor>


#include <qwhatsthis.h>
#include <qpainter.h>
#include <qwt_plot.h>
#include <qwt_symbol.h>
#include <qwt_scale_map.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>

class QwtPlot;
class QwtPlotCurve;

#define ICV_CURVE_ACTIVATED         (1)
#define ICV_CURVE_UNACTIVATED       (2)
#define ICV_CURVE_MAX_MARKER_NUM    (40)
#define ICV_CURVE_SHOW_MARKER       (1)
#define ICV_CURVE_HIDE_MARKER       (2)

class IcvPlotCurve  
{

public:
    IcvPlotCurve(QwtPlotCurve *crv);
    IcvPlotCurve();
    ~IcvPlotCurve();

    QwtPlot *getPlot();
    void setPlot(QwtPlot *plt);

    QwtPlotCanvas *getCanvas();
    void setCanvas(QwtPlotCanvas *cvs);

    QwtPlotCurve *getCurve();
    void setCurve(QwtPlotCurve *crv);

    qint16 getActivateState();
    void setActivateState(qint16 state);
    void deleteCurve();
    void showCurve();
    void hideCurve();

    void setMarker();
    QList<QwtPlotMarker *> getMarkers();
    void showMarkers();
    void hideMarkers();
    void deleteMakers();
    qint16 getShowMarkerState();
    void setShowMarkerState(qint16 state);

    void setColor(QColor color);
    void setWidth(qint16 width);
    void setStyle(Qt::PenStyle style);
    void setMarker(QwtSymbol::Style style);
    void setMarkerSize(qint16 size);

private:
    QwtPlot       *plot;
    QwtPlotCanvas *canvas;
    QwtPlotCurve  *curve;
    QList<QwtPlotMarker *> markers;
    qint16         activateState ;
    qint16         showMarkerState;

};

#endif
