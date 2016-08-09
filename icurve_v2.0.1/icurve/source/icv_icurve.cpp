#include <Qt>
#include <QObject>
#include <QtGui>
#include <QDialog>  
#include <QMessageBox>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QInputDialog>
#include <QDir>
#include <QIcon>
#include <QPair>
#include <QList>
#include <QSize>
#include <QRegExp>
#include <QComboBox>
#include <QDebug>
#include <QVariant>
#include <QMimeData>
#include <QSettings>

#include <qwt_legend.h>
#include <qwt_plot_renderer.h>
#include <qwt_legend_label.h>
#include <qwt_plot_item.h>
#include "icv_icurve.h"
#include "icv_curve_filter.h"
#include "icv_penstyle.h"
#include "icv_curve_property.h"
#include "icv_marker_property.h"
#include "icv_clipboard.h"
#include "icv_symbol.h"
#include "icv_curve_info.h"
#include "icv_axse_scale.h"
#include "icv_about.h"


/*including tone index at head of the line*/
#define ICV_MAX_NUM_DIGITS_PERLINE          (11)  

#define ICV_PLOT_DATA_START_POS             (1)
#define ICV_MAX_LINE_NUM_BACKGROUD_PROCESS  (200)

#define ICV_MAX_RECENT_FILE_NUM             (5)



IcvICurve::IcvICurve(QWidget *parent, Qt::WFlags flags) : QMainWindow(parent, flags)
{
    ui.setupUi(this);

    createExtraActions();
    createExtraMenus();

    initMainWinStyle(this);

    plot = new QwtPlot();
    initMainPlotter(plot);

    QVBoxLayout *centralLayout = new QVBoxLayout(this);
    centralLayout->addWidget(plot);
    centralLayout->setContentsMargins(10,10,30,10);

    QWidget *widget = new QWidget();
    widget->setLayout(centralLayout);
    setCentralWidget(widget);

    plotCanvas = new IcvPlotCanvas(this) ;
    plotCanvas->createCurvePopMenuAction();
    plotCanvas->createCurvePopMenu();

    analyProgressDialog  = NULL;
    isDataAnalyCanceled  = false;

    /*{{{signals and slots*/
    connect(ui.actionOpen,           SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui.actionSaveAs,         SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui.actionClose,          SIGNAL(triggered()), this, SLOT(closePlot()));
    connect(ui.actionExit,           SIGNAL(triggered()), this, SLOT(close()));
    /* edit menu */
    connect(ui.actionRefresh,        SIGNAL(triggered()), this, SLOT(refreshPlot()));
    connect(ui.actionCut,            SIGNAL(triggered()), this, SLOT(cutCurve()));
    connect(ui.actionCopy,           SIGNAL(triggered()), this, SLOT(copyCurve()));
    connect(ui.actionPaste,          SIGNAL(triggered()), this, SLOT(pasteCurve()));
    connect(ui.actionRemove,         SIGNAL(triggered()), this, SLOT(removeCurves()));
    connect(ui.actionHide,           SIGNAL(triggered()), this, SLOT(hideCurves()));
    connect(ui.actionShow,           SIGNAL(triggered()), this, SLOT(showCurves()));
    connect(ui.actionDelete,         SIGNAL(triggered()), this, SLOT(deleteCurve()));
    connect(ui.actionFind,           SIGNAL(triggered()), this, SLOT(findCurve()));
    connect(ui.actionShowAll,        SIGNAL(triggered()), this, SLOT(showAllCurve()));
    connect(ui.actionSelectAll,      SIGNAL(triggered()), this, SLOT(selectAllCurves()));  
    connect(ui.actionSelectInvert,   SIGNAL(triggered()), this, SLOT(selectInvertCurves()));  
    /* curve menu */
    connect(ui.actionColor,          SIGNAL(triggered()), this, SLOT(setCurveColor()));
    connect(ui.actionWidth,          SIGNAL(triggered()), this, SLOT(setCurveWidth()));
    connect(ui.actionStyle,          SIGNAL(triggered()), this, SLOT(setCurveStyle()));
    connect(ui.actionMarker,         SIGNAL(triggered()), this, SLOT(setCurveMarker()));
    connect(ui.actionExpand,         SIGNAL(triggered()), this, SLOT(expandCurve()));
    connect(ui.actionFilter,         SIGNAL(triggered()), this, SLOT(filterCurve()));
    connect(ui.actionInfo,           SIGNAL(triggered()), this, SLOT(showCurveInfo()));
    connect(ui.actionCurveProperties,SIGNAL(triggered()), this, SLOT(setCurveProperties()));
    /* axse menu */
    connect(ui.actionAxseScale,      SIGNAL(triggered()), this, SLOT(setAxseScale()));
    connect(ui.actionAxseTitle,      SIGNAL(triggered()), this, SLOT(setAxseTitle()));
    connect(ui.actionAxseAlignment,  SIGNAL(triggered()), this, SLOT(setAxseAlignment()));
    connect(ui.actionAxseRotation,   SIGNAL(triggered()), this, SLOT(setAxseRotation()));
    /* insert menu */
    connect(ui.actionTitle,          SIGNAL(triggered()), this, SLOT(insertTitle()));
    connect(ui.actionX_label,        SIGNAL(triggered()), this, SLOT(insertXLabel()));
    connect(ui.actionY_label,        SIGNAL(triggered()), this, SLOT(insertYLabel()));
    connect(ui.actionLegend,         SIGNAL(triggered()), this, SLOT(insertLegend()));
    connect(ui.actionCurveName,      SIGNAL(triggered()), this, SLOT(insertCurveName()));
    connect(ui.actionFooter,         SIGNAL(triggered()), this, SLOT(insertFooter()));
    connect(ui.actionIndicator,      SIGNAL(triggered()), this, SLOT(insertIndicator()));
    /* view menu */
    connect(ui.actionZoom,           SIGNAL(triggered(bool)), this, SLOT(enableZoomer(bool)));
    /* tool menu */
    connect(ui.actionHandMove,       SIGNAL(triggered(bool)), this, SLOT(enableHandMove(bool)));
    /* help menu */
    connect(ui.actionAbout,          SIGNAL(triggered()),  this, SLOT(aboutIcurve()));
    /* others */
    connect(this, SIGNAL(analyDataProgress(qint32)), this, SLOT(updateAnalyProgressBar(qint32)));
    /*}}}*/
}


IcvICurve::~IcvICurve()
{

}


void IcvICurve::initMainWinStyle(QMainWindow *self)
{
    self->setWindowTitle("iCurve");
    self->setContentsMargins(0,0,0,0);

    QPalette mainWinPalette;
    mainWinPalette.setColor(QPalette::Background,Qt::lightGray);
    self->setPalette(mainWinPalette);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/3);

    /* shortcuts */
    ui.actionOpen->setShortcut(QKeySequence::Open);
    ui.actionSaveAs->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    ui.actionFilter->setShortcut(QKeySequence::Find);
    ui.actionSelectAll->setShortcut(QKeySequence::SelectAll);
    ui.actionSelectInvert->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_A);
    ui.actionShowAll->setShortcut(Qt::CTRL + Qt::Key_K);
    ui.actionRemove->setShortcut(QKeySequence::Delete);
    ui.actionDelete->setShortcut(Qt::CTRL + Qt::Key_Delete);
    ui.actionRefresh->setShortcut(QKeySequence::Refresh);
    ui.actionExpand->setShortcut(Qt::CTRL + Qt::Key_G);

    return ;
}


void IcvICurve::initMainPlotter(QWidget *plotWidget)
{
    QwtPlot *plot = static_cast<QwtPlot*>(plotWidget);

    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, -150.0, 150.0 );
    plot->setAxisScale( QwtPlot::xBottom, 0, 3000 );

    plot->setAxisLabelAlignment(QwtPlot::xBottom,Qt::AlignLeft);
    plot->setAxisLabelAlignment(QwtPlot::yLeft,Qt::AlignTop);

    plot->plotLayout()->setAlignCanvasToScales( false );
    plot->plotLayout()->setCanvasMargin(0);

    /* legendItem, default curve title is displayed */
    legendItem = new QwtPlotLegendItem();  
    legendItem->attach(plot);

    /* legend */
    legend = new QwtLegend;
    legend->setDefaultItemMode( QwtLegendData::Checkable );
    connect(legend, SIGNAL(checked(const QVariant &, bool, int)), this,
        SLOT(legendChecked( const QVariant &, bool)));

    /* grid */
    grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::DashLine));
    grid->setMinorPen(QPen(Qt::DashLine));  
    grid->attach( plot );

    /* magnifier */
    magnifier = new QwtPlotMagnifier(plot->canvas());
    magnifier->setEnabled(true);

    /* panner */
    panner = new QwtPlotPanner(plot->canvas());
    //panner->setMouseButton( Qt::MidButton );
    panner->setEnabled(true);

    /* picker */
    picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                               QwtPlotPicker::CrossRubberBand, 
                               QwtPicker::AlwaysOn,
                               plot->canvas());
    picker->setStateMachine( new QwtPickerDragPointMachine() );
    picker->setRubberBandPen( QColor( Qt::green ) );
    picker->setRubberBand( QwtPicker::CrossRubberBand );
    picker->setTrackerPen( QColor( Qt::black ) );

    /* zoomer */
    zoomer = new QwtPlotZoomer(plot->canvas());
    zoomer->setRubberBandPen( QColor( Qt::darkGreen ) );
    zoomer->setTrackerMode( QwtPlotPicker::AlwaysOn );
    /* RightButton: zoom out by 1,Ctrl+RightButton:zoom 
       out to full size */
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );

    zoomer->setRubberBand( QwtPicker::RectRubberBand );
    zoomer->setRubberBandPen( QColor( Qt::green ) );
    zoomer->setTrackerMode( QwtPicker::ActiveOnly );
    zoomer->setTrackerPen( QColor( Qt::white ) );
    zoomer->setEnabled(false);
    zoomer->zoom(0);
    connect(zoomer, SIGNAL(zoomed(const QRectF&)), this, SLOT(zoomPlot(QRectF&)));

    return;
}


void IcvICurve::createExtraActions()
{
    /* create extra actions */
    for (qint16 cnt = 0; cnt < ICV_MAX_RECENT_FILE_NUM; cnt++)
    {
        QAction* action = new QAction(this);
        action->setVisible(false);
        connect(action, SIGNAL(triggered()),this, SLOT(openRecentFile()));
        recentFileActs.append(action);
    }
    return;
}


void IcvICurve::createExtraMenus()
{
    /* create extra menus*/
    for (qint16 cnt = 0; cnt < ICV_MAX_RECENT_FILE_NUM; cnt++)
        ui.menuFile->addAction(recentFileActs[cnt]);
    updateRecentFileActions();
    return;
}


void IcvICurve::openFile()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
            tr("Open file..."),
            fileInfo.absolutePath(),
            tr("Text files (*.txt *.log *.cap *.bak);;All Files (*)"));

    if(fileNames.isEmpty())
    {
        return; 
    }

    /* save file info */
    fileInfo.setFile(fileNames[0]);
    for(qint16 fileCnt = 0; fileCnt < fileNames.count(); fileCnt++)
    {
        /* before loading new data, get data postion for a new file */
        qint16 posCurRepository = plotData.count();

        /* parse and analyze file content */
        if(ICU_OK != loadData(fileNames[fileCnt]))
            continue;

        /* when a new file exported, should not start from scratch */
        for(qint16 pos = posCurRepository; pos < plotData.count(); pos++)
        {
            QwtPlotCurve *qwtCurve = new QwtPlotCurve();
            qwtCurve->setPen(QColor::fromHsl(rand()%360,rand()%256,rand()%200), 1.0, Qt::SolidLine);
            qwtCurve->setSamples(plotData[pos].getData().toVector());

            QwtSymbol *symbol = new QwtSymbol(QwtSymbol::NoSymbol,
                                              QBrush(Qt::yellow),
                                              QPen(Qt::red, 2),
                                              QSize(2, 2));
            qwtCurve->setSymbol(symbol);
            qwtCurve->setTitle(plotData.value(pos).getCommandTitle());
            qwtCurve->setStyle(QwtPlotCurve::Lines);
            qwtCurve->attach(plot);

            IcvPlotCurve *plotCurve = new IcvPlotCurve;
            plotCurve->setCurve(qwtCurve);
            plotCurve->setCanvas(plotCanvas);
            plotCurve->setDataPos(pos);
            plotCurve->setCommand(plotData[pos]);
            plotCurve->setAttachedState(true);
            /* attach curves to plot canvas*/
            plotCanvas->appendCurves(plotCurve);
        }
        /* append file to recent file list */
        setCurrentFile(fileNames[fileCnt]);
    }

    plot->replot();
    return;
}


void IcvICurve::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    QString fileName = action->data().toString();
    /* save file info */
    fileInfo.setFile(fileName);
    /* before loading new data, get data postion for a new file */
    qint16 posCurRepository = plotData.count();

    /*analyze file content */
    if(ICU_OK != loadData(fileName))
        return;

    /* when a new file exported, should not start from scratch */
    for(qint16 pos = posCurRepository; pos < plotData.count(); pos++)
    {
        QwtPlotCurve *qwtCurve = new QwtPlotCurve();
        qwtCurve->setPen(QColor::fromHsl(rand()%360,rand()%256,rand()%200), 1.0, Qt::SolidLine);
        qwtCurve->setSamples(plotData[pos].getData().toVector());

        QwtSymbol *symbol = new QwtSymbol(QwtSymbol::NoSymbol,
                                          QBrush(Qt::yellow),
                                          QPen(Qt::red, 2),
                                          QSize(2, 2));
        qwtCurve->setSymbol(symbol);
        qwtCurve->setTitle(plotData.value(pos).getCommandTitle());
        qwtCurve->setStyle(QwtPlotCurve::Lines);
        qwtCurve->attach(plot);

        IcvPlotCurve *plotCurve = new IcvPlotCurve;
        plotCurve->setCurve(qwtCurve);
        plotCurve->setCanvas(plotCanvas);
        plotCurve->setDataPos(pos);
        plotCurve->setCommand(plotData[pos]);
        plotCurve->setAttachedState(true);
        /* attach curves to plot canvas*/
        plotCanvas->appendCurves(plotCurve);
    }
    /* append file to recent file list */
    setCurrentFile(fileName);

    plot->replot();
    return;
}


void IcvICurve::setCurrentFile(const QString &fileName)
{
    QSettings settings("tmp/history.ini",QSettings::IniFormat);;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > ICV_MAX_RECENT_FILE_NUM)
    {
        files.removeLast();
    }

    settings.setValue("recentFileList", files);
    foreach (QWidget *widget, QApplication::topLevelWidgets())
    {
        IcvICurve *mainWin = qobject_cast<IcvICurve *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }
    return;
}


void IcvICurve::saveAs()
{
    QwtPlotRenderer renderer;
    QString plotTitle;

    if(plot != NULL)
        plotTitle = plot->title().text();
    else
        plotTitle = "";

    renderer.exportTo(plot, plotTitle);

    return;
}


void IcvICurve::closePlot()
{
    delete plot;
    plot = NULL;

    return;
}


void IcvICurve::insertTitle()
{
    bool ok;
    QString origTitle = plot->title().text();
    QString      text = QInputDialog::getText(this, tr("Input"),
                        tr("Plot title:"), QLineEdit::Normal, origTitle, &ok);
    if (ok)
        plot->setTitle(text);

    return;
}


void IcvICurve::insertXLabel()
{
    bool ok;
    QString origLabel = plot->axisTitle(QwtPlot::xBottom).text();
    QString      text = QInputDialog::getText(this, tr("Input"),
        tr("X lable:"), QLineEdit::Normal, origLabel, &ok);
    if (ok)
        plot->setAxisTitle(QwtPlot::xBottom,text);
    return;
}


void IcvICurve::insertYLabel()
{
    bool ok;
    QString origLabel = plot->axisTitle(QwtPlot::yLeft).text();
    QString      text = QInputDialog::getText(this, tr("Input"),
        tr("Y lable:"), QLineEdit::Normal, origLabel, &ok);
    if (ok)
        plot->setAxisTitle(QwtPlot::yLeft,text);
    return ;
}


void IcvICurve::insertLegend()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        ui.actionLegend->setChecked(false);
        return ;
    }

    if(true == ui.actionLegend->isChecked())
    {
        legend = new QwtLegend(plot);
        legend->setDefaultItemMode( QwtLegendData::Checkable );
        connect(legend, SIGNAL(checked(const QVariant &, bool, int)), this,
            SLOT(legendChecked( const QVariant &, bool)));

        plot->insertLegend(legend, QwtPlot::RightLegend );
        ui.actionLegend->setChecked(true);
    }
    else
    {
        plot->insertLegend(NULL);
        /* qwtplot will delete legend internally */
        legend = NULL;
        ui.actionLegend->setChecked(false);
    }
    return;
}


void IcvICurve::insertCurveName()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        ui.actionCurveName->setChecked(false);
        return ;
    }

    if(true == ui.actionCurveName->isChecked())
    {
        legendItem->attach(plot);
        ui.actionCurveName->setChecked(true);
    }
    else
    {
        legendItem->detach();
        ui.actionCurveName->setChecked(false);
    }

    plot->replot();
    return;
}


void IcvICurve::insertFooter()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Input"),
        tr("Footer"), QLineEdit::Normal, "", &ok);
    if (ok)
        plot->setFooter(text);
    return;
}


void IcvICurve::insertIndicator()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        ui.actionIndicator->setChecked(false);
        return ;
    }

    if(true == ui.actionIndicator->isChecked())
    {
        for(qint16 cnt = 0; cnt < allCurves.count(); cnt++)
        {
            if(!allCurves.at(cnt)->isAttached())
                continue;

            QList<QwtPlotMarker *>indicators = allCurves.at(cnt)->getIndicators();
            if(!indicators.isEmpty())
                continue;

            /* if not indicator attached to the curve, create and attach*/
            QPointF maxSample;
            QPointF minSample;
            QPointF sample;

            maxSample.setX(0);
            maxSample.setY(0);

            minSample.setX(0xff);
            minSample.setY(0xff);
            for(qint16 posX = 0; posX < allCurves.at(cnt)->getCurve()->dataSize(); posX++)
            {
                sample = allCurves.at(cnt)->getCurve()->sample(posX);
                if(sample.ry() >  maxSample.ry())
                {
                    maxSample.setX(posX);
                    maxSample.setY(sample.ry());
                }

                if(sample.ry()!= 0 && sample.ry() < minSample.ry())
                {
                    minSample.setX(posX);
                    minSample.setY(sample.ry());
                }
            }

            QString name = allCurves.at(cnt)->getCommand().getCommandTitle();
            QwtPlotMarker *maxPosMarker = new QwtPlotMarker();
            maxPosMarker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
            maxPosMarker->setItemAttribute( QwtPlotItem::Legend, false );
            maxPosMarker->setSymbol( new IcvSymbol(IcvSymbol::Arrow) );
            maxPosMarker->setValue(maxSample);
            maxPosMarker->setLabel(QString("max(%1,%2)").arg(maxSample.rx()).arg(maxSample.ry()));
            maxPosMarker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
            maxPosMarker->attach(plot);

            QwtPlotMarker *minPosMarker = new QwtPlotMarker();
            minPosMarker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
            minPosMarker->setItemAttribute( QwtPlotItem::Legend, false );
            minPosMarker->setSymbol( new IcvSymbol(IcvSymbol::Arrow) );
            minPosMarker->setValue(minSample);
            minPosMarker->setLabel( QString("min(%1,%2)").arg(minSample.rx()).arg(minSample.ry()));
            minPosMarker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
            minPosMarker->attach(plot);

            QList<QwtPlotMarker *>markers;
            markers.append(maxPosMarker);
            markers.append(minPosMarker);
            allCurves.at(cnt)->setIndicator(markers);

            ui.actionIndicator->setChecked(true);
        }
    }
    else
    {
        for(qint16 cnt = 0; cnt < allCurves.count(); cnt++)
        {
            allCurves.at(cnt)->deleteIndicator();
        }

        ui.actionIndicator->setChecked(false);
    }

    plot->replot();
    return;
}


void IcvICurve::setCurveColor()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *>selectedCurve = plotCanvas->getSelectedCurve();
    if(0 == selectedCurve.count())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return;
    }

    QColor color = QColorDialog::getColor(Qt::white,this);
    if(!color.isValid())
        return;

    for(qint16 cnt = 0; cnt < selectedCurve.count(); cnt++)
    {
        selectedCurve.at(cnt)->setColor(color);
    }

    plot->replot();
    return;
}


void IcvICurve::setCurveWidth()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> selectedCurve = plotCanvas->getSelectedCurve();
    if(0 == selectedCurve.count())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    bool ok;
    qint16 width = QInputDialog::getInt(this, tr("Input"),tr("Group size:"), 
        1, 1, 20, 1, &ok);

    for(qint16 cnt = 0; cnt < selectedCurve.count(); cnt++)
    {
        selectedCurve.at(cnt)->setWidth(width);
    }
    return;
}


void IcvICurve::setCurveStyle()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> selectedCurve = plotCanvas->getSelectedCurve();
    if(0 == selectedCurve.count())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    QDialog *curveStyleDlg = new QDialog(this);

    QLabel *titleLabel = new QLabel(curveStyleDlg);
    titleLabel->setText("Select style:");

    QComboBox *styleComboBox = new QComboBox(curveStyleDlg);
    styleComboBox->setObjectName("styleComboBox");
    styleComboBox->setItemDelegate(new IcvPenStyleDelegate((QObject *)styleComboBox));
    styleComboBox->addItem(tr("Solid"),     Qt::SolidLine);
    styleComboBox->addItem(tr("Dash"),      Qt::DashDotLine);
    styleComboBox->addItem(tr("Dot"),       Qt::DotLine);
    styleComboBox->addItem(tr("DashDot"),   Qt::DashDotLine);
    styleComboBox->addItem(tr("DashDotDot"),Qt::DashDotDotLine);

    QDialogButtonBox *btnBox = new QDialogButtonBox(curveStyleDlg);
    btnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(btnBox,SIGNAL(accepted()),curveStyleDlg,SLOT(accept()));
    connect(btnBox,SIGNAL(rejected()),curveStyleDlg,SLOT(reject()));

    QGridLayout *gridLayout  = new QGridLayout(curveStyleDlg);  
    gridLayout->addWidget(titleLabel,0,0);  
    gridLayout->addWidget(styleComboBox,0,1);  
    gridLayout->addWidget(btnBox,1,1);  
    gridLayout->setRowMinimumHeight(1,50);

    qint16 retcode = (qint16)curveStyleDlg->exec();
    if(QDialog::Accepted == retcode)
    {
        QComboBox *child = curveStyleDlg->findChild<QComboBox *>("styleComboBox");
        Qt::PenStyle style = static_cast<Qt::PenStyle>(child->currentIndex() + 1);

        for(qint16 cnt = 0; cnt < selectedCurve.count(); cnt++)
        {
            selectedCurve.at(cnt)->setStyle(style);
        }

        plot->replot();
    }

    delete curveStyleDlg;
    curveStyleDlg = NULL;
    return;
}


void IcvICurve::setCurveMarker()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> selectedCurve = plotCanvas->getSelectedCurve();
    if(0 == selectedCurve.count())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    IcvMarkerPropertyDialog *markrPropDlg = new IcvMarkerPropertyDialog(this);
    qint16 retcode = (qint16)markrPropDlg->exec();
    if(QDialog::Accepted == retcode)
    {
        QComboBox *childTypeComboBox = markrPropDlg->findChild<QComboBox *>("typeComboBox");
        QwtSymbol::Style style = static_cast<QwtSymbol::Style>(childTypeComboBox->currentIndex());

        for(qint16 cnt = 0; cnt < selectedCurve.count(); cnt++)
        {
            selectedCurve.at(cnt)->setMarker(style);

            QLineEdit *childSizeLineEdit = markrPropDlg->findChild<QLineEdit *>("sizeLineEdit");
            QString   size = childSizeLineEdit->text();
            if(size != "")
            {
                bool ok = false;
                selectedCurve.at(cnt)->setMarkerSize(size.toInt(&ok));
            }

            QBrush brush = markrPropDlg->getMarkerBrush();
            QPen   pen   = markrPropDlg->getMarkerPen();
            selectedCurve.at(cnt)->setMarkerColor(brush,pen);
        }

        plot->replot();
    }

    delete markrPropDlg;
    return;
}


void IcvICurve::refreshPlot()
{
    plot->replot();
    return;
}


void IcvICurve::cutCurve()
{
    return ;
}
 

void IcvICurve::copyCurve()
{
    if(NULL == plotCanvas)
        return;

    QList<IcvPlotCurve*> curves = plotCanvas->getSelectedCurve();
    IcvClipBoard  clipBoard;
    for(qint16 cnt = 0; cnt < curves.count(); cnt++)
    {
        clipBoard.data.append(plotData.at(curves.at(cnt)->getDataPos()));
    }

    QVariant data;

    QList<QPointF> plotdata = plotData[0].getData();
#if 0
    data.setValue<QList<QPointF>>(plotdata);

    QList<QPointF>  clipBoard2 = data.value<QList<QPointF>>();

    bool isCanConvet = data.canConvert(QVariant::BitArray);

    QByteArray byteStream = data.toByteArray();

    QMimeData mime;

    mime.setData("IcvClipBoard",byteStream);

    QClipboard *board = QApplication::clipboard();
    board->setMimeData(&mime);
#endif

    return;
}


void IcvICurve::pasteCurve()
{
    QClipboard *board = QApplication::clipboard();  
    QString       str = board->text();  
    return;
}


void IcvICurve::filterCurve()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    IcvCurveFilterDialog *filterDlg = new IcvCurveFilterDialog(this);
    filterDlg->setWindowTitle("Filter curves");
    if(filterDlg->exec() != QDialog::Accepted)
        return;

    QString    keyword = filterDlg->getKeyword();
    qint16  filterType = filterDlg->getLookupType();

    QList<IcvPlotCurve *> curves = plotCanvas->getCurves();
    QList<IcvPlotCurve *> curvesFound;
    for(qint16 cnt = 0; cnt < curves.count(); cnt++)
    {
        qint16 dataPos = curves.at(cnt)->getDataPos();
        IcvCommand cmd = plotData[dataPos];
        bool   isMatch = false;

        if(ICV_BY_COMPLETECOMAND == filterType)
        {
            QString completeComand = cmd.getName() + " " + QString::number(cmd.getLineId()) +
                " " + QString::number(cmd.getDirection());
            isMatch = (completeComand.compare(keyword, Qt::CaseInsensitive) == 0)?
                true : false;
        }

        else if (ICV_BY_COMANDNAME == filterType)
        {
            isMatch = (cmd.getName().compare(keyword, Qt::CaseInsensitive)== 0)?
                true : false;
        }
        else if (ICV_BY_LINEID == filterType)
        {
            QString strLineId = QString::number(cmd.getLineId());
            isMatch = (keyword == strLineId) ? true : false;
        }
        else if (ICV_BY_DIRECTION == filterType)
        {
            QString strDir = (cmd.getDirection() == 1) ? "DS":"US";
            isMatch = (keyword.compare(strDir, Qt::CaseInsensitive) == 0)? 
                true : false;
        }

        if(true == isMatch)   
        {
            curvesFound.push_back(curves.at(cnt));
        }
    } 

    if(0 == curvesFound.count()) 
    {
        QMessageBox::information(this,tr("Info"), tr("No curves filtered!"));
        return;
    }

    /* remove the curves from list of deletion*/
    QList<IcvPlotCurve*> targetCurves = plotCanvas->getCurves();
    for(qint16 cnt = 0; cnt < targetCurves.count(); cnt++)
    {
        for(qint16 cntF = 0; cntF < curvesFound.count(); cntF++)
        {
            targetCurves.removeAll(curvesFound.at(cntF));
        }
    }
    plotCanvas->removeCurves(targetCurves);

    plot->updateLegend();
    plot->replot();
    /*clear memory*/
    delete filterDlg;
    return;
}


void IcvICurve::filterCurvePreview(qint16 type, QString keyword)
{
    QList<IcvPlotCurve *> curves = plotCanvas->getCurves();
    QList<IcvPlotCurve *> curvesFound;
    for(qint16 cnt = 0; cnt < curves.count(); cnt++)
    {
        qint16 dataPos = curves.at(cnt)->getDataPos();
        IcvCommand cmd = plotData[dataPos];

        bool isMatch  = false;
        if(ICV_BY_COMPLETECOMAND == type)
        {
            QString completeComand = cmd.getName() + " " + QString::number(cmd.getLineId()) +
                " " + QString::number(cmd.getDirection());
            isMatch = (completeComand.compare(keyword, Qt::CaseInsensitive) == 0)?
                true : false;
        }

        else if (ICV_BY_COMANDNAME == type)
        {
            isMatch = (cmd.getName().compare(keyword, Qt::CaseInsensitive)== 0)?
                true : false;
        }
        else if (ICV_BY_LINEID == type)
        {
            QString strLineId = QString::number(cmd.getLineId());
            isMatch = (keyword == strLineId) ? true : false;
        }
        else if (ICV_BY_DIRECTION == type)
        {
            QString strDir = (cmd.getDirection() == 1) ? "DS":"US";
            isMatch = (keyword.compare(strDir, Qt::CaseInsensitive) == 0)? 
                true : false;
        }

        if(true == isMatch)   
        {
            curvesFound.push_back(curves.at(cnt));
        }
    } 

    /*retrieve the bak of all curve list*/
    QList<IcvPlotCurve*> targetCurves = plotCanvas->getCurves();
    for(qint16 cnt = 0; cnt < targetCurves.count(); cnt++)
    {
        for(qint16 cntF = 0; cntF < curvesFound.count(); cntF++)
        {
            targetCurves.removeAll(curvesFound.at(cntF));
        }
    }

    /* process the left curves */
    for(qint16 cnt = 0; cnt < targetCurves.count(); cnt++)
    {
        QwtPlotCurve *curve = targetCurves.at(cnt)->getCurve();
        curve->hide();
    }

    plot->replot();
    return;
}


void IcvICurve::recoverCurveVisible()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    for(qint16 cnt = 0; cnt < allCurves.count(); cnt++)
    {
        QwtPlotCurve *curve = allCurves.at(cnt)->getCurve();
        curve->show();
    }

    plot->replot();
    return;
}


void IcvICurve::findCurve()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    IcvCurveFilterDialog *filterDlg = new IcvCurveFilterDialog(this);
    filterDlg->setWindowTitle("Find curves");
    if(filterDlg->exec() != QDialog::Accepted)
        return;

    QString    keyword = filterDlg->lineEdit->text();
    qint16  filterType = filterDlg->getLookupType();

    QList<IcvPlotCurve *> curves = plotCanvas->getCurves();
    QList<IcvPlotCurve *> curvesFound;
    for(qint16 cnt = 0; cnt < curves.count(); cnt++)
    {
        qint16 dataPos = curves.at(cnt)->getDataPos();
        IcvCommand cmd = plotData[dataPos];

        bool isMatch  = false;
        if(ICV_BY_COMPLETECOMAND == filterType)
        {
            QString completeComand = cmd.getName() + " " + QString::number(cmd.getLineId()) +
                " " + QString::number(cmd.getDirection());
            isMatch = (completeComand.compare(keyword, Qt::CaseInsensitive) == 0)?
                true : false;
        }

        else if (ICV_BY_COMANDNAME == filterType)
        {
            isMatch = (cmd.getName().compare(keyword, Qt::CaseInsensitive)== 0)?
                true : false;
        }
        else if (ICV_BY_LINEID == filterType)
        {
            QString strLineId = QString::number(cmd.getLineId());
            isMatch = (keyword == strLineId) ? true : false;
        }
        else if (ICV_BY_DIRECTION == filterType)
        {
            QString strDir = (cmd.getDirection() == 1) ? "DS":"US";
            isMatch = (keyword.compare(strDir, Qt::CaseInsensitive) == 0)? 
                true : false;
        }

        if(true == isMatch)   
        {
            curvesFound.push_back(curves.at(cnt));
        }
    } 

    plotCanvas->highlightCurve(curvesFound);
    plotCanvas->setCurSelectCurves(curvesFound);
    plot->replot();

    /*clear memory*/
    delete filterDlg;
    filterDlg = NULL;
    return;
}


void IcvICurve::deleteCurve()
{
    if(NULL == plotCanvas)
        return ;

    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> selCurve = plotCanvas->getSelectedCurve();
    if(selCurve.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }
    QList<IcvPlotCurve*> curves = plotCanvas->getSelectedCurve();
    plotCanvas->deleteCurve(curves);
    plot->replot();
    return;
}


void IcvICurve::removeCurves()
{
    if(NULL == plotCanvas)
        return ;

    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> selCurve = plotCanvas->getSelectedCurve();
    if(selCurve.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    plotCanvas->removeSelectCurves();
    plot->replot();
    return;
}


void IcvICurve::hideCurves()
{
    if(NULL == plotCanvas)
        return ;

    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> selCurve = plotCanvas->getSelectedCurve();
    if(selCurve.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    plotCanvas->hideSelectCurves();
    plot->replot();
    return;
}


void IcvICurve::showCurves()
{
    if(NULL == plotCanvas)
        return ;

    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }
    QList<IcvPlotCurve *> selCurve = plotCanvas->getSelectedCurve();
    if(selCurve.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    plotCanvas->showSelectCurves();
    plot->replot();
    return;
}


void IcvICurve::showAllCurve()
{
    if(NULL == plotCanvas)
        return;

    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curves plotted, maybe file not opened."));
        return ;
    }

    for(qint16 pos = 0; pos < allCurves.count(); pos++)
        allCurves.at(pos)->showCurve();

    plot->replot();
    return;
}


void IcvICurve::selectAllCurves()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return;
    }

    plotCanvas->highlightCurve(allCurves);
    plotCanvas->setCurSelectCurves(allCurves);
    plot->replot();
    return;
}


void IcvICurve::selectInvertCurves()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> curve = plotCanvas->getSelectedCurve();
    for(qint16 cnt = 0; cnt < curve.count(); cnt++)
    {
        curve.at(cnt)->hideMarkers();
        allCurves.removeAll(curve.at(cnt));
    }

    QList<IcvPlotCurve *> reversedCurves = allCurves;
    plotCanvas->highlightCurve(reversedCurves);
    plotCanvas->setCurSelectCurves(reversedCurves);
    plot->replot();
    return;
}


void IcvICurve::expandCurve()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> curve = plotCanvas->getSelectedCurve();
    if(curve.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    bool ok;
    int groupSize = QInputDialog::getInt(this, tr("Input"),tr("Group size:"), 
                                         4, 1, 8, 2, &ok);
    if (!ok)
    {
        QMessageBox::information(this,tr("Error"),tr("group size may not be correct."));
        return ;
    }

    for(qint16 cnt = 0; cnt < curve.count(); cnt++)
    {
        curve.at(cnt)->setGroupSize(groupSize);
    }

    plot->replot();
    return;
}


void IcvICurve::legendChecked( const QVariant &itemInfo, bool on)
{
    QwtPlotItem *plotItem = plot->infoToItem(itemInfo);
    if(NULL == plotItem)
        return ;

    plotItem->setVisible( on );
    QwtLegend *lgd = dynamic_cast<QwtLegend *>(legend);
    QList<QWidget *> legendWidgets = lgd->legendWidgets(plot->itemToInfo(plotItem));
    if (legendWidgets.size() == 1)
    {
        QwtLegendLabel *legendLabel =
            dynamic_cast<QwtLegendLabel *>(legendWidgets[0]);

        if (legendLabel)
            legendLabel->setChecked( on );
    }

    plot->replot();
    return ;
}


void IcvICurve::showCurveInfo()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> curve = plotCanvas->getSelectedCurve();
    if(curve.isEmpty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    IcvCommand  cmd =  plotData.at(curve.at(0)->getDataPos());
    IcvCurveInfoDialog *infoDlg = new IcvCurveInfoDialog(curve, this, Qt::Dialog);
    infoDlg->exec();
    return;
}


void IcvICurve::setCurveProperties()
{
    QList<IcvPlotCurve*> allCurves = plotCanvas->getCurves();
    if(allCurves.empty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve in canvas."));
        return ;
    }

    QList<IcvPlotCurve *> curve = plotCanvas->getSelectedCurve();
    if(curve.isEmpty())
    {
        QMessageBox::information(this,tr("Info"),tr("No curve selected."));
        return ;
    }

    IcvCurvePropertyDialog *propDiag = new IcvCurvePropertyDialog(curve, this, Qt::Dialog);
    propDiag->resize(400,150);
    propDiag->exec();
    return;
}


QwtPlotZoomer* IcvICurve::getZoomer()
{
    return zoomer;
}


void IcvICurve::enableZoomer( bool checked)
{
    bool enable = checked;
    zoomer->setEnabled(enable);
    plotCanvas->setZoomState(enable);
    /* disable magnifier and panner */
    magnifier->setEnabled(!enable);
    panner->setEnabled(!enable);

    if(checked)
        plotCanvas->getCanvas()->setCursor(Qt::CrossCursor);
    else if(ui.actionHandMove->isChecked())
        plotCanvas->getCanvas()->setCursor(Qt::OpenHandCursor);
    else
        plotCanvas->getCanvas()->setCursor(Qt::ArrowCursor);

    ui.actionZoom->setCheckable(true);
    ui.actionZoom->setChecked(checked);
    plot->replot();
    return;
}


void IcvICurve::enableHandMove( bool checked)
{
    /* magnifier and panner are compliant with 
       hand-move */
    magnifier->setEnabled(checked);
    panner->setEnabled(checked);
    /* zoomer is only enabled*/
    if(!checked && true == ui.actionZoom->isChecked())
        zoomer->setEnabled(true);
    else
        zoomer->setEnabled(false);

    if(checked)
        plotCanvas->getCanvas()->setCursor(Qt::OpenHandCursor);
    else if(ui.actionZoom->isChecked())
        plotCanvas->getCanvas()->setCursor(Qt::CrossCursor);
    else
        plotCanvas->getCanvas()->setCursor(Qt::ArrowCursor);

    ui.actionHandMove->setCheckable(true);
    ui.actionHandMove->setChecked(checked);

    plot->replot();
    return;
}

bool IcvICurve::isHandMoveChecked()
{
    return ui.actionHandMove->isChecked();
}


void IcvICurve::zoomPlot(const QRectF &rect)
{
 //   plotCanvas->setZoomState(true);
    return;
}


void IcvICurve::setAxseScale()
{
    IcvAxseSCaleDialog *axseScaleDlg = new IcvAxseSCaleDialog(this);

    axseScaleDlg->setWindowTitle("Axse scale dialog");
    if(axseScaleDlg->exec() != QDialog::Accepted)
        return ;

    bool   ok    = false;
    double minX  = axseScaleDlg->lineEditMinX->text().toDouble(&ok);
    double maxX  = axseScaleDlg->lineEditMaxX->text().toDouble(&ok);
    double minY  = axseScaleDlg->lineEditMinY->text().toDouble(&ok);
    double maxY  = axseScaleDlg->lineEditMaxY->text().toDouble(&ok);

    plot->setAxisScale(QwtPlot::xBottom, minX, maxX, 0);
    plot->setAxisScale(QwtPlot::yLeft, minY, maxY, 0);
    plot->replot();
    return;
}


void IcvICurve::setAxseTitle()
{
   /* the same as insert x/y label */
    QDialog *axseTitleDlg = new QDialog(this);

    QLabel *labelX = new QLabel("Axse X:");
    QLineEdit *textEditX = new QLineEdit(axseTitleDlg);
    textEditX->setObjectName(QString(tr("textEditX")));
    textEditX->resize(40,20); 

    QLabel *labelY = new QLabel("Axse Y:");
    QLineEdit *textEditY = new QLineEdit(axseTitleDlg);
    textEditY->setObjectName(tr("textEditY"));
    textEditY->resize(40,20);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(axseTitleDlg);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), axseTitleDlg, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), axseTitleDlg, SLOT(reject()));

    QGridLayout *layout = new QGridLayout(axseTitleDlg);
    layout->addWidget(labelX,0,0,1,1);
    layout->addWidget(textEditX,0,1,1,1);
    layout->addWidget(labelY,1,0,1,1);
    layout->addWidget(textEditY,1,1,1,1);
    layout->addWidget(buttonBox,2,1);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,3);
    layout->setRowStretch(0,1);
    layout->setRowStretch(1,1);
    layout->setRowMinimumHeight(1,20);

    /*alignment*/
    layout->setAlignment(Qt::AlignTop|Qt::AlignRight);
    axseTitleDlg->setLayout(layout);
    axseTitleDlg->resize(250,40);

    qint16 retcode = (qint16)axseTitleDlg->exec();
    if(QDialog::Accepted == retcode)
    {
        QLineEdit *child = NULL;

        child = axseTitleDlg->findChild<QLineEdit *>("textEditX");
        QString titleX = child->text();
        plot->setAxisTitle(QwtPlot::xBottom,titleX);

        child = axseTitleDlg->findChild<QLineEdit *>("textEditY");
        QString titleY = child->text();
        plot->setAxisTitle(QwtPlot::yLeft,titleY);

    }

    delete axseTitleDlg;
    return;
}


void IcvICurve::setAxseAlignment()
{
    QDialog *axseAlignDlg = new QDialog(this);
    axseAlignDlg->setWindowTitle("Axse aliagment");

    QLabel *labelHor = new QLabel("Horizontal");
    QLabel *labelVer = new QLabel("Vertical");

    QLabel *labelX = new QLabel("X:");
    QComboBox *alignComboHX = new QComboBox(axseAlignDlg);
    alignComboHX->setObjectName("alignComboHX");
    alignComboHX->addItem(tr("Left"));
    alignComboHX->addItem(tr("Right"));
    alignComboHX->addItem(tr("Center"));

    QComboBox *alignComboVX = new QComboBox(axseAlignDlg);
    alignComboVX->setObjectName("alignComboVX");
    alignComboVX->addItem(tr("Top"));
    alignComboVX->addItem(tr("Bottom"));
    alignComboVX->addItem(tr("Center"));

    QLabel *labelY = new QLabel("Y:");
    QComboBox *alignComboHY = new QComboBox(axseAlignDlg);
    alignComboHY->setObjectName("alignComboHY");
    alignComboHY->addItem(tr("Left"));
    alignComboHY->addItem(tr("Right"));
    alignComboHY->addItem(tr("Center"));

    QComboBox *alignComboVY = new QComboBox(axseAlignDlg);
    alignComboVY->setObjectName("alignComboVY");
    alignComboVY->addItem(tr("Top"));
    alignComboVY->addItem(tr("Bottom"));
    alignComboVY->addItem(tr("Center"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(axseAlignDlg);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), axseAlignDlg, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), axseAlignDlg, SLOT(reject()));

    QGridLayout *layout = new QGridLayout(axseAlignDlg);
    layout->addWidget(labelHor,     0, 1, 1, 1);
    layout->addWidget(labelVer,     0, 2, 1, 1);
    layout->addWidget(labelX,       1, 0, 1, 1);
    layout->addWidget(alignComboHX, 1, 1, 1, 1);
    layout->addWidget(alignComboVX, 1, 2, 1, 1);
    layout->addWidget(labelY,       2, 0, 1, 1);
    layout->addWidget(alignComboHY, 2, 1, 1, 1);
    layout->addWidget(alignComboVY, 2, 2, 1, 1);
 /* ok and cancel button span 2 column */
    layout->addWidget(buttonBox,    3, 1, 1, 2); 
    /*alignment*/
    layout->setAlignment(Qt::AlignTop|Qt::AlignRight);
    axseAlignDlg->setLayout(layout);
    axseAlignDlg->setFixedSize(200,120);

    qint16 retcode = (qint16)axseAlignDlg->exec();
    if(QDialog::Accepted == retcode)
    {
        QComboBox *childH = NULL;
        QComboBox *childV = NULL;
        bool ok;

        childH = axseAlignDlg->findChild<QComboBox *>("alignComboHX");
        childV = axseAlignDlg->findChild<QComboBox *>("alignComboVX");
        Qt::Alignment alignX = childH->currentText().toInt(&ok) |
                               childV->currentText().toInt(&ok) ;
        plot->setAxisLabelAlignment(QwtPlot::xBottom,alignX);

        childH = axseAlignDlg->findChild<QComboBox *>("alignComboHY");
        childV = axseAlignDlg->findChild<QComboBox *>("alignComboVY");
        Qt::Alignment alignY = childH->currentText().toInt(&ok) |
                               childV->currentText().toInt(&ok) ;
        plot->setAxisLabelAlignment(QwtPlot::yLeft,alignY);

    }

    delete axseAlignDlg;
    return;
}


void IcvICurve::setAxseRotation()
{
    QDialog *axseRotationDlg = new QDialog(this);

    QLabel *labelX = new QLabel("Angle for X:");
    QLineEdit *textEditX = new QLineEdit(axseRotationDlg);
    textEditX->setObjectName(QString(tr("textEditX"))); 

    QLabel *labelY = new QLabel("Angle for Y:");
    QLineEdit *textEditY = new QLineEdit(axseRotationDlg);
    textEditY->setObjectName(tr("textEditY"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(axseRotationDlg);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), axseRotationDlg, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), axseRotationDlg, SLOT(reject()));

    QGridLayout *layout = new QGridLayout(axseRotationDlg);
    layout->addWidget(labelX,0,0,1,1);
    layout->addWidget(textEditX,0,1,1,1);
    layout->addWidget(labelY,1,0,1,1);
    layout->addWidget(textEditY,1,1,1,1);
    layout->addWidget(buttonBox,2,1);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,3);
    layout->setRowStretch(0,1);
    layout->setRowStretch(1,2);
    layout->setRowMinimumHeight(1,20);

    /*alignment*/
    layout->setAlignment(Qt::AlignTop|Qt::AlignRight);
    axseRotationDlg->setLayout(layout);

    qint16 retcode = (qint16)axseRotationDlg->exec();
    if(QDialog::Accepted == retcode)
    {
        QLineEdit *child = NULL;
        bool ok;

        child = axseRotationDlg->findChild<QLineEdit *>("textEditX");
        double angleX = child->text().toDouble(&ok);
        plot->setAxisLabelRotation(QwtPlot::xBottom,angleX);

        child = axseRotationDlg->findChild<QLineEdit *>("textEditY");
        double angleY = child->text().toDouble(&ok);
        plot->setAxisLabelRotation(QwtPlot::yLeft,angleY);
    }

    delete axseRotationDlg;
    return;
}


void IcvICurve::setAxseProperties()
{
    return;
}


void IcvICurve::aboutIcurve()
{
    IcvAboutDialog *dlg = new IcvAboutDialog(this);
    dlg->show();
    return;
}


ICU_RET_STATUS IcvICurve::loadData(const QString &filename)
{
    QFile file(filename);
    if(!file.exists())
    {
        return ICU_FILE_NOT_EXIST;
    }

    if(!file.open(QFile::ReadOnly ))
    {
        return ICU_FILE_READ_ERROR;
    }

    if(ICU_OK != analyzeData(file))
    {
        return ICU_PLOT_DATA_FORMAT_ERROR;
    }
    return ICU_OK;
}


ICU_RET_STATUS IcvICurve::analyzeData(QFile &file)
{
    qint32     cout = 0;
    bool       ok   = true;
    qint32     line = 0;
    qint32     totalLineNum = 0;
    QRegExp    regExp; 
    IcvCommand cmd;
    IcvCommand prevCmd;

    QTextStream dataTextStream(&file);
    totalLineNum = 0;
    while (!dataTextStream.atEnd()) 
    {
        QString line = dataTextStream.readLine();
        totalLineNum++; 
    }

    if(totalLineNum > ICV_MAX_LINE_NUM_BACKGROUD_PROCESS)
    {
        analyProgressDialog = new QProgressDialog(plot);
        analyProgressDialog->setModal(true);
        analyProgressDialog->setRange(0, totalLineNum);
        analyProgressDialog->setWindowTitle("File analyzing...");
        /* display immediately */
        analyProgressDialog->show();
        analyProgressDialog->repaint();
        connect(analyProgressDialog, SIGNAL(canceled()), this, SLOT(cancelAnalyProgressBar()));
    }

    dataTextStream.seek(0);
    isDataAnalyCanceled = false;
    line = 0;
    while(!dataTextStream.atEnd() && !isDataAnalyCanceled)
    {
        line++;
        QString dataLine = dataTextStream.readLine();
        qint16       pos = 0;
        QString curCmdName("NULL");
        QString curPromt("NULL");
        QString lineId("NULL");
        QString direction("NULL");

        QRegExp cmdRegExp;
        cmdRegExp.setPattern(cmd.getTitlePattern());
        cmdRegExp.setCaseSensitivity(Qt::CaseInsensitive);
        bool isMatch = dataLine.contains(cmdRegExp);
        if(isMatch)
        {
            /* if the last command is not empty, terminate it */
            prevCmd = cmd;

            QStringList caps = cmdRegExp.capturedTexts();
            QString promt    = caps[1];
            QString nameCap  = caps[2];
            QString name;
            for(qint16 i = 0; i < cmd.getFamily().count(); i++)
            {
                if(!cmd.getFamily().value(i).compare(nameCap, Qt::CaseInsensitive))
                    name = cmd.getFamily().value(i);
            }

            bool  ok = false;
            qint16 lineId    = caps[3].toInt(&ok);
            qint16 direction = caps[4].toInt(&ok);

            /* preparing the new command */
            cmd.reset();
            cmd.setPrompt(promt);
            cmd.setName(name);
            cmd.setLineId(lineId);
            cmd.setDirection(direction);
            cmd.setDataPosInFile(line);
            cmd.setBriefInfo(dataLine);
            cmd.setFileName(file.fileName());
            /* set cmd matched state */
            cmd.setState(CMD_TITLE_MATCHED);

            continue;
        }

        if(CMD_GROUPSIZE_MATCHED != cmd.getState() || CMD_PLOTDATA_MATCHED != cmd.getState())
        {
            /* math groupsize, if found, loop continue */
            if(cmd.matchGroupSize(dataLine))
            {
                cmd.setState(CMD_GROUPSIZE_MATCHED);
                continue;
            }
        }

        /* command already started, try to parse data */
        if(prevCmd.getData().count() > 0)              
        {
            /* reset previous command */
            plotData.push_back(prevCmd);   
            prevCmd.reset();
        }

        qint16 ret = assembleData(dataLine,&cmd);
        if(ret == ICU_PLOT_DATA_FORMAT_ERROR)
        {
            QString error = file.fileName() + " at line " + QString::number(line) \
                + ":data format incorrect.";
            QMessageBox::critical(this,"ERROR",error);

            return ICU_PLOT_DATA_FORMAT_ERROR; 
        }

        if((NULL != analyProgressDialog) && (line%100 == 0))
            emit analyDataProgress(line);
    }
    /* no more new command found when at file end, save the current data */
    if(cmd.getData().count() > 0)     
    {
        cmd.setState(CMD_CLOSED);
        plotData.push_back(cmd);   
    }

    /* importing data action halted, data should also be cleared */
    if(isDataAnalyCanceled)
        plotData.clear();

    if((NULL != analyProgressDialog))
    {
        delete analyProgressDialog;
        analyProgressDialog = NULL;
    }

    return ICU_OK; 
}


ICU_RET_STATUS IcvICurve::assembleData(QString dataLine, IcvCommand *cmd)
{
    /* spectial format pre-processing */
    if((cmd->getName() == "getTxPsd") && dataLine.contains("---"))
    {
        dataLine = dataLine.replace("---","-150.0");
    }
    else if((cmd->getName() == "getRmcBitAlloc"))
    {
        if(dataLine.contains(QRegExp("\\s+x\\s+")))
            dataLine = dataLine.replace("x","0");
    }

    QRegExp regExpr;
    regExpr.setCaseSensitivity(Qt::CaseInsensitive);
    regExpr.setPattern(cmd->getDataPattern());
    if(-1 == regExpr.indexIn(dataLine))
    {
        return ICU_OK;
    }

    /* plot data collection start */
    cmd->setState(CMD_PLOTDATA_MATCHED);
    /* begin to parse data */
    QStringList splitList;
    splitList = dataLine.split(QRegExp("\\s+|\\,"),QString::SkipEmptyParts);
    qint16 n = splitList.count();
    /* filter some type of date like: 11, -11, -11.1 */
    QStringList digList;
    digList = splitList.filter(QRegExp("^\\d+$|^\\d+\\.\\d$|^-\\d+\\.\\d$"));
    qint16 n2 = digList.count();
    if(digList.isEmpty())
        return ICU_OK;

    if(ICU_OK != appendCommandData(cmd, digList))
        return ICU_ERROR;

    if(digList.count() < ICV_MAX_NUM_DIGITS_PERLINE)
    {
        cmd->setState(CMD_CLOSED);
        return ICU_OK;
    }

    return ICU_OK;
}


ICU_RET_STATUS IcvICurve::appendCommandData(IcvCommand *cmd, QStringList data)
{
    bool ok = false;
    QList<QPointF> points; 
    QPointF        point;
    qint16         tone = 0;

    if(0 == cmd->getData().count())
        tone = data.at(0).toInt(&ok);  
    else
        tone = cmd->getData().count();

    for(qint16 i = ICV_PLOT_DATA_START_POS; i < data.count(); i++)
    {

        qreal dataItem = data.at(i).toFloat(&ok);

        if(dataItem > 20)
        {
            break;
        }
        if(false == ok)
            return ICU_PLOT_DATA_FORMAT_ERROR;
        tone++;
        point.setX(tone);
        point.setY(dataItem);
        points.append(point);
    }

    cmd->setData(points,true);
    return ICU_OK;
}


QList <IcvCommand>* IcvICurve::getPlotData()
{
    return &plotData;
}


void IcvICurve::updateAnalyProgressBar(qint32 progress)
{
    if(analyProgressDialog != NULL)
    {
        analyProgressDialog->setValue(progress);
        analyProgressDialog->setLabelText(QString("%1/%2").arg(progress).arg(analyProgressDialog->maximum()));
        analyProgressDialog->repaint();
    }
    return ;
}


void IcvICurve::cancelAnalyProgressBar()
{
    isDataAnalyCanceled = true;
    return;
}


void IcvICurve::updateRecentFileActions()
{
    QSettings settings("tmp/history.ini",QSettings::IniFormat);;
    QStringList files = settings.value("recentFileList").toStringList();
    qint16 numRecentFiles = qMin(files.size(), (int)ICV_MAX_RECENT_FILE_NUM);

    for (qint16 i = 0; i < numRecentFiles; i++) 
    {
        QString text = tr("&%1 %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (qint16 j = numRecentFiles; j < ICV_MAX_RECENT_FILE_NUM; ++j)
    {
        recentFileActs[j]->setVisible(false);
    }

    return;
}


QwtPlot* IcvICurve::getPlot()
{
    return plot;
}


QwtPlotMagnifier* IcvICurve::getMagnifier()
{
    return magnifier;
}


void IcvICurve::paintEvent ( QPaintEvent * event )
{
    return QWidget::paintEvent(event);
}


void IcvICurve::mouseMoveEvent ( QMouseEvent * event )
{
    return QWidget::mouseMoveEvent(event);
}


