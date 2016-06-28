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

#include "icv_icurve.h"
#include "icv_plot_curve.h"

class QPoint;
class QPointF;
class QCustomEvent;
class QwtPlot;
class QPolygonF;
class QwtPlotCurve;
class IcvICurve;
class IcvPlotCurve;

class IcvPlotCanvas : public QWidget
{
    Q_OBJECT

public:
    IcvPlotCanvas(IcvICurve *parent);
    ~IcvPlotCanvas();

    IcvICurve* retrieveParent();
    void setMainWin(IcvICurve *icurve);
    //IcvICurve* getMainWin();

    QwtPlotCanvas *getCanvas();
    void setCanvas(QwtPlotCanvas *cvs);

    QCursor getCursor();
    void setCursor(QCursor csr);
    void restoreCursor();

    QList<IcvPlotCurve *> getCurves();
    void setCurves(QList<IcvPlotCurve *> crvs);
    void setCurSelectCurves(QList<IcvPlotCurve *> crvs);
    void initCurves();
    void updateCurves();
    void lookforCurves();
    void appendCurves(IcvPlotCurve *curve);
    void clearCurves(QList<IcvPlotCurve *> crvs);
    void removeSelectCurves();
    void clearAllCurves();
    QList<IcvPlotCurve*> getSelectedCurve();
    void deleteCurve(QList<IcvPlotCurve*> crv);
    void removeCurves(QList<IcvPlotCurve *> crv);
    void highlightCurve(QList<IcvPlotCurve*> crv);
    void hideSelectCurves();
    void showSelectCurves();
    void lockMagnifier();
    void unlockMagnifier();
    void setZoomState(bool state);
    void createCurvePopMenu();
    void createCurvePopMenuAction();

    virtual bool eventFilter( QObject *, QEvent * );
    virtual bool event( QEvent * );

private:
    void onMouseLeftButtonClick(const QMouseEvent *event);
    void onMouseRightButtonClick(const QMouseEvent *event);
    void onMouseMove(const QMouseEvent *event);

private:
    QwtPlotCanvas *canvas;
    IcvICurve     *mainWin;
    QList<IcvPlotCurve *> curves;
    QList<IcvPlotCurve *> curSelectedCurve;
    QList<IcvPlotCurve *> prevSelectedCurve;

    /*menus*/
    QMenu *crvSelPopMenu;
    QMenu *subCrvSelWidthMenu;
    QMenu *subCrvSelStyleMenu;
    QMenu *subCrvSelMarkeStyleMenu;
    QMenu *subCrvSelMarkerSizeMenu;
    QMenu *subCrvSelGroupSizeMenu;

    /*actions*/
    QAction *cutAction;
    QAction *copyAction;
    QAction *delAction;
    QAction *rmvAction;
    QAction *colorSetAction;
    QAction *propertySetAction;

    /*action groups*/
    QActionGroup *widthActGrp;
    QActionGroup *styleActGrp;
    QActionGroup *markerStyleActGrp;
    QActionGroup *markerSizeActGrp;
    QActionGroup *groupSizeActGrp;

    bool lockCursorMoveAction;
    bool zoomStateEnabled;
    QCursor cursor;

private slots:
        void setCurveColor();
        void setCurveWidth(QAction *action);
        void setCurveStyle(QAction *action);
        void setCurveMarker(QAction *action);
        void setCurveMarkerSize(QAction *action);
        void setCurveGroupSize(QAction *action);
        void setCurveProperty();
        void deleteSelectCurve();
};

#endif
