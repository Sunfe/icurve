#ifndef ICURVE_H
#define ICURVE_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QRectF>

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#include "ui_icurve.h"
#include "canvasPicker.h"
#include "curvePropertyDialog.h"

class iCurve : public QMainWindow
{
    Q_OBJECT

        /*function members*/
    public:
        iCurve(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~iCurve();

    public:
        QwtPlot *getPlot();
        CanvasPicker *getPicker();
        CurvePropertyDialog *getPropertyDialog();

    protected:
        void contextMenuEvent ( QContextMenuEvent * event );
        void paintEvent(QPaintEvent *event);
        bool eventFilter ( QObject * watched, QEvent * event ) ;
        void mouseDoubleClickEvent ( QMouseEvent * event );
        void mousePressEvent ( QMouseEvent * event );

        private slots:
            void openFile();
        void saveAs();
        /*
           void CutCurve();
           void CopyCurve();

         */
        void editTitle();
        void delCurve();

        void setColor();
        void setWidth(QAction *action);
        void setStyle(QAction *action);
        void setMarker(QAction *action);
        void setMarkerSize(QAction *action);
        void setProperty();
        void about();

    private:
        void createMenus();
        void createActions();
        bool loadData(const QString &vFile);
        /*}}}*/


        /*{{{data members*/
        private:
        Ui::iCurveClass ui;

        QwtPlot *plot;
        QwtPlotGrid *grid;
        QwtSymbol *symbol;
        CanvasPicker *pCanvasPicker;
        QRectF titleRect;
        QLabel *label;

        QFileInfo fileInfo;

        private:
        /*menus*/
        QMenu *mainPopMenu;
        QMenu *widthMenu;
        QMenu *styleMenu;
        QMenu *markerMenu;
        QMenu *marSizeMenu;

        /*actions*/
        QAction *cut;
        QAction *copy;
        QAction *del;
        QAction *color;
        QAction *prop;

        /*action groups*/
        QActionGroup *widthGroup;
        QActionGroup *styleGroup;
        QActionGroup *markerGroup;
        QActionGroup *markerSizeGroup;

        CurvePropertyDialog *propDiag;
        };

#endif // ICURVE_H
