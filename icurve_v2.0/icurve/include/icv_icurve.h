#ifndef ICURVE_H
#define ICURVE_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QRectF>
#include <QProgressDialog>
#include <QFileInfo>
#include <QAbstractItemDelegate>  
#include <QPainter>  

#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_engine.h>
#include <qwt_color_map.h>
#include <qwt_text.h>
#include <qwt_text_engine.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_legenditem.h>
#include <qwt_plot_grid.h>

#include "ui_icurve.h"
#include "ui_icv_curve_filter.h"

#include "icurve_common.h"
#include "icv_command.h"
#include "icv_plot_canvas.h"

class IcvPlotCanvas;

class IcvICurve : public QMainWindow
{
    Q_OBJECT

public:
    IcvICurve(QWidget *parent = 0, Qt::WFlags flags = 0);
    void initMainPlotter(QWidget *plotWidget);
    void initMainWinStyle(QMainWindow *self);

    ICU_RET_STATUS loadData(const QString &filename);
    ICU_RET_STATUS analyzeData(QFile &file);
    ICU_RET_STATUS assembleData(QString dataLine, IcvCommand *cmd);
    QList <IcvCommand> *getPlotData();
    QwtPlot* getPlot();
    QwtPlotMagnifier* getMagnifier();

    ~IcvICurve();

protected:
    void paintEvent ( QPaintEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );

private:
    Ui::icurveClass ui;
    Ui::IcvCurveFilterDialog *curveFilterDialog;

    /*Qt objects*/
    QRectF titleRect;
    QLabel *label;
    QProgressDialog *analyProgressDialog;
    QFileInfo fileInfo;

    /*Qwt objects*/	
    QwtPlot *plot;
    QwtPlotGrid *grid;
    QwtPlotMagnifier *magnifier;
    QwtSymbol *symbol;
    
    IcvPlotCanvas *plotCanvas;
    QList <IcvCommand> plotData;
    bool isDataAnalyCanceled;

private slots:
    void openFile();
    void insertTitle();
    void insertXLabel();
    void insertYLabel();
    void insertFooter();
    void insertLegend();
    void expandCurve();
    void filterCurve();
    void showAllCurve();
    void legendChecked( const QVariant &itemInfo, bool on );
    void updateAnalyProgressBar(qint16 progress);
    void cancelAnalyProgressBar();


signals:
    void analyDataProgress(qint16 progress);

};


#endif // ICURVE_H
