#ifndef ICV_PLOT_CANVAS_H
#define ICV_PLOT_CANVAS_H

#include <qobject.h>
#include <QtGlobal>
#include <QMenu>
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


class IcvPlotCanvas : public QWidget
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

    void createCurvePopMenus();
    void createCurvePopMenuActions();

    virtual bool eventFilter( QObject *, QEvent * );
    virtual bool event( QEvent * );


private:
    void onMouseLeftButtonClick(const QPoint &);
    void onMouseRightButtonClick(const QPoint &);
    void onMouseMove(const QPoint &);

private:
    QwtPlot *plot;
    QwtPlotCanvas *canvas;
    IcvPlotCurve *curSelectedCurve;
    IcvPlotCurve *prevSelectedCurve;
    QList<IcvPlotCurve *> curves;


    /*menus*/
    QMenu *crvSelPopMenu;
    QMenu *subCrvSelWidthMenu;
    QMenu *subCrvSelStyleMenu;
    QMenu *subCrvSelMarkeStyleMenu;
    QMenu *subCrvSelMarkerSizeMenu;

    /*actions*/
    QAction *cutAction;
    QAction *copyAction;
    QAction *delAction;
    QAction *colorSetAction;
    QAction *propertySetAction;

    /*action groups*/
    QActionGroup *widthActGrp;
    QActionGroup *styleActGrp;
    QActionGroup *markerStyleActGrp;
    QActionGroup *markerSizeActGrp;


private slots:
    void setCurveColor(IcvPlotCurve *curve);
    void seCurvetWidth(IcvPlotCurve *curve, QAction *action);
    void setCurveStyle(IcvPlotCurve *curve, QAction *action);
    void setCurveMarker(IcvPlotCurve *curve, QAction *action);
    void setCurveMarkerSize(IcvPlotCurve *curve, QAction *action);
    void setCurveProperty(IcvPlotCurve *curve);

};

#endif
