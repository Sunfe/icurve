#ifndef ICURVE_H
#define ICURVE_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QRectF>
#include <QProgressDialog>
#include <QFileInfo>

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_panner.h>
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
#include "icurve_common.h"
#include "command.h"


class icurve : public QMainWindow
{
    Q_OBJECT

public:
    icurve(QWidget *parent = 0, Qt::WFlags flags = 0);
    void initMainPlotter(QWidget *plotWidget);
    void initMainWinStyle(QMainWindow *self);

    ICU_RET_STATUS loadData(const QString &filename);
    ICU_RET_STATUS analyzeData(QFile &file);
    ICU_RET_STATUS assembleData(QString dataLine, Command *cmd);

    ~icurve();

protected:
    void paintEvent ( QPaintEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );

private:
    Ui::icurveClass ui;

    /*Qt objects*/
    QRectF titleRect;
    QLabel *label;
    QProgressDialog *analyProgressDialog;
    QFileInfo fileInfo;

    /*Qwt objects*/	
    QwtPlot *plot;
    QwtPlotGrid *grid;
    QwtSymbol *symbol;

    QList <Command> plotData;

private slots:
    void openFile();
    void updateAnalyProgressBar(qint16 progress);

signals:
    void analyDataProgress(qint16 progress);

};

#endif // ICURVE_H
