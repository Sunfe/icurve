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
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include "ui_icurve.h"
#include "ui_icv_curve_filter.h"
#include "icurve_common.h"
#include "icv_command.h"
#include "icv_plot_canvas.h"
#include "icv_curve_differ.h"
#include "icv_cliparser.h"

#define ICV_EYESCAN_MARGIN                   (10)

class IcvPlotCanvas;
class IcvCurveDiffer;

class IcvICurve : public QMainWindow
{
    Q_OBJECT

public:
    IcvICurve(QWidget *parent = 0, Qt::WFlags flags = 0);
    void initMainPlotter(QWidget *plotWidget);
    void initMainWinStyle(QMainWindow *self);
    void createExtraActions();
    void createExtraMenus();
    void setCurrentFile(const QString &fileName);
    void loadFile(QStringList fileNames);
    ICU_RET_STATUS loadData(const QString &filename);
    ICU_RET_STATUS analyzeFile(QFile &file);
    ICU_RET_STATUS analyzeTextStream(QTextStream &streamText, QString steamName);
    ICU_RET_STATUS assembleData(QString dataLine, IcvCommand *cmd);
    ICU_RET_STATUS appendCommandData(IcvCommand *cmd, QStringList data);
    void setAxseEyeSpan();
    QList <IcvCommand> *getPlotData();
    QwtPlot* getPlot();
    QwtPlotMagnifier* getMagnifier();
    QwtPlotZoomer *getZoomer();
    QwtPlotPicker *getPicker();
    bool isHandMoveChecked();
    void taskDelay(qint32 mseconds);
    QProgressDialog * createIcvProgressDiag(QWidget *parent, int rangeMin, int rangeMax, QString winTitle,
        QString LabelText, QSize size, bool isModal);
    void updateStatusBar();
    void resetDifferTool();
    ~IcvICurve();

protected:
    void paintEvent ( QPaintEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::icurveClass ui;
    Ui::IcvCurveFilterDialog *curveFilterDialog;
    QList<QAction *> recentFileActs;
    /*Qt objects*/
    QRectF titleRect;
    QLabel *label;
    QProgressDialog *analyProgressDialog;
    QFileInfo fileInfo;
    /*Qwt objects*/	
    QwtPlot *plot;
    QwtLegend *legend;
    QwtPlotLegendItem *legendItem;
    QwtPlotGrid *grid;
    QwtPlotMagnifier *magnifier;
    QwtPlotPicker *picker;
    QwtPlotPanner *panner;
    QwtPlotZoomer *zoomer;
    QwtSymbol *symbol;
    IcvCurveDiffer *differTool;
    IcvPlotCanvas *plotCanvas;
    QList <IcvCommand> plotData;
    bool isDataAnalyCanceled;

private slots:
        /*file menu slots*/
        void openFile();
        void openRecentFile();
        void newFile();
        void saveAs();
        void exportData();
        void closePlot();
        void plotBlockData(QString data);
        /*edit menu slots*/
        void refreshPlot();
        void cutCurve();
        void copyCurve();
        void pasteCurve();
        void removeCurves();
        void hideCurves();
        void showCurves();
        void deleteCurves();
        void deleteCurvesAll();
        void findCurve();
        void showAllCurve();
        void selectAllCurves();
        void selectInvertCurves();
        /*data menu slots*/
        void jumpToFilePos();
        void viewCurveData();
        void viewCurveStat();
        /*curve menu slots*/
        void setCurveColor(); 
        void setCurveWidth();
        void setCurveStyle();
        void setCurveMarker();
        void expandCurve();
        void filterCurve();
        void filterCurvePreview(qint16 type, QString keyword);
        void recoverCurveVisible();
        void showCurveInfo();
        void setCurveProperties();
        /*curve Axse slots*/
        void setAxseScale();
        void setAxseTitle();
        void setAxseAlignment();
        void setAxseRotation();
        void setAxseProperties();
        /*insert menu slots*/
        void insertTitle();
        void insertXLabel();
        void insertYLabel();
        void insertLegend();
        void insertCurveName();
        void insertFooter();
        void insertIndicator();
        /*view tool slots*/
        void enableZoomer(bool checked);
        void zoomPlot(const QRectF &rect);
        void diffCurves();
        void parseCliData();
        void enableHandMove(bool checked);
        /* help help slots */
        void aboutIcurve();

        void legendChecked( const QVariant &itemInfo, bool on );
        void updateAnalyProgressBar(qint32 progress);
        void cancelAnalyProgressBar();
        void updateRecentFileActions();
signals:
        void analyDataProgress(qint32 progress);
        void displayCurveInfoSignal(QString name, QString position, QString lineInfo);
        void sigDiffCurve(QList<IcvPlotCurve *>);

};


#endif // ICURVE_H
