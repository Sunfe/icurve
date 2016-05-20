#include "icurve.h"

#include <QtGui>
#include <QPair>
#include <QList>
#include <QSize>
#include <Qt>
#include <QDialog>
#include <QIcon>
#include <QMessageBox>
#include <QDir>

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_renderer.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_engine.h>
#include <qwt_plot_legenditem.h>
#include <qwt_color_map.h>
#include <qwt_text.h>
#include <qwt_text_engine.h>
#include <qwt_plot_layout.h>

#include "editPlotDialog.h"
#include "ui_about.h"

iCurve::iCurve(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{

    /*most important thing*/
    ui.setupUi(this);

    setWindowTitle("iCurve");
    setWindowIcon(QIcon(":/images/iCurve.ico"));
    setStatusBar(NULL);
    setContentsMargins(5,5,50,5);

    QPalette mainWinPalette;
    mainWinPalette.setColor(QPalette::Background,Qt::lightGray);
    setPalette(mainWinPalette);


    /*plot widget init*/
    plot = new QwtPlot();

#if 0
    QFont axFont("Times", 10, QFont::Normal);
    plot->setAxisFont(QwtPlot::xBottom, axFont);
    plot->setAxisFont(QwtPlot::yLeft, axFont);
#endif

    plot->setTitle( "unamed" );
    plot->setAxisTitle(QwtPlot::xBottom, "X");
    plot->setAxisTitle(QwtPlot::yLeft, "Y");

    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, -150.0, 150.0 );
    plot->setAxisScale( QwtPlot::xBottom, 0, 5000 );
    plot->setAxisLabelAlignment(QwtPlot::xBottom,Qt::AlignLeft);
    plot->setAxisLabelAlignment(QwtPlot::yLeft,Qt::AlignTop);
    plot->plotLayout()->setAlignCanvasToScales( false );
    plot->plotLayout()->setCanvasMargin(0);

    QwtPlotLegendItem *le= new QwtPlotLegendItem();
    le->attach(plot);

    grid = new QwtPlotGrid();
    grid->setMajPen(QPen(Qt::DashLine));
    grid->setMinPen(QPen(Qt::DashLine));
    grid->attach( plot );

    ( void ) new QwtPlotPanner( plot->canvas());
    ( void ) new QwtPlotMagnifier(plot->canvas());
    pCanvasPicker =  new CanvasPicker( plot );


    setCentralWidget(plot);

    createActions();
    createMenus();

    /*signals & slots*/
    connect(ui.actionOpen,SIGNAL(triggered()),this, SLOT(openFile()));
    connect(ui.actionClose,SIGNAL(triggered()),this, SLOT(close()));
    connect(ui.actionSaveAs,SIGNAL(triggered()),this, SLOT(saveAs()));
    connect(ui.actionTitle,SIGNAL(triggered()),this, SLOT(editTitle()));
    connect(ui.actionAbout,SIGNAL(triggered()),this, SLOT(about()));

}


iCurve::~iCurve()
{

}


void iCurve::createMenus()
{
    mainPopMenu = new QMenu(this);
    mainPopMenu->addAction(del);
    mainPopMenu->addAction(color);

    widthMenu = new QMenu("width",this);
    widthMenu->addActions(widthGroup->actions());
    mainPopMenu->addMenu(widthMenu);

    styleMenu = new QMenu("style",this);
    styleMenu->addActions(styleGroup->actions());
    mainPopMenu->addMenu(styleMenu);

    markerMenu = new QMenu("Marker",this);
    markerMenu->addActions(markerGroup->actions());
    mainPopMenu->addMenu(markerMenu);

    marSizeMenu = new QMenu("Marker size",this);
    marSizeMenu->addActions(markerSizeGroup->actions());
    mainPopMenu->addMenu(marSizeMenu);

    mainPopMenu->addAction(prop);

}

void iCurve::createActions()
{
    QAction *action = NULL;

    /*delete the curve*/
    del = new QAction(QIcon(":/images/delete.png"),tr("Delete"),this);
    del->setShortcut(QKeySequence::Delete);
    del->setStatusTip("delete seleted curve");
    connect(del,SIGNAL(triggered()),this,SLOT(delCurve()));

    /*color the curve*/
    color = new QAction(tr("Color..."),this);
    color->setStatusTip("color the seleted curve");
    connect(color,SIGNAL(triggered()),this,SLOT(setColor()));

    /*{{{set width action*/
    widthGroup = new QActionGroup(this);
    qint8 i;
    QString actionText;
    for(i = 0; i< 12; i++)
    {
        action = new QAction(widthGroup);
        if(0 == i)
        {
            actionText = QString::number(0.5);
            action->setText(actionText);
            action->setData(0.5);
        }
        else if(11 == i)
        {
            actionText = QString::number(12);
            action->setText(actionText);
            action->setData(12);
        }
        else
        {
            actionText = QString::number(i);
            action->setText(actionText);
            action->setData(i);
        }

    }
    connect(widthGroup,SIGNAL(triggered(QAction *)),this,SLOT(setWidth(QAction *)));

    /*}}}*/

    /*{{{curve styleMenu action*/
    QList < QPair<QString,int> > styleList;
    styleList.append(qMakePair(tr("Solid"),1));
    styleList.append(qMakePair(tr("Dash"),2));
    styleList.append(qMakePair(tr("Dot"),3));
    styleList.append(qMakePair(tr("DashDot"),4));
    styleList.append(qMakePair(tr("DashDotDot"),5));

    styleGroup = new QActionGroup(this);
    QList <QPair<QString,int> >::iterator s;
    for(s = styleList.begin(); s < styleList.end(); s++)
    {
        action = new QAction(styleGroup);
        action->setText((s->first));
        action->setData((s->second));
    }
    connect(styleGroup,SIGNAL(triggered(QAction *)),this,SLOT(setStyle(QAction *)));
    /*}}}*/

    /*{{{curve marker action*/
    QList< QPair<QString,int> > markerList;
    markerList.append(qMakePair(tr("None"),-1));
    markerList.append(qMakePair(tr("Ellipse"),0));
    markerList.append(qMakePair(tr("Rect"),1));
    markerList.append(qMakePair(tr("Diamond"),2));
    markerList.append(qMakePair(tr("Triangle"),3));
    markerList.append(qMakePair(tr("DTriangle"),4));
    markerList.append(qMakePair(tr("UTriangle"),5));
    markerList.append(qMakePair(tr("LTriangle"),6));
    markerList.append(qMakePair(tr("RTriangle"),7));
    markerList.append(qMakePair(tr("Cross(+)"),8));
    markerList.append(qMakePair(tr("XCross(x)"),9));
    markerList.append(qMakePair(tr("HLine"),10));
    markerList.append(qMakePair(tr("VLine"),11));
    markerList.append(qMakePair(tr("Star1"),12));
    markerList.append(qMakePair(tr("Star2"),13));
    markerList.append(qMakePair(tr("Hexagon"),14));

    markerGroup = new QActionGroup(this);
    QList <QPair<QString,int> >::iterator m;
    for(m = markerList.begin(); m < markerList.end(); m++)
    {
        action = new QAction(markerGroup);
        action->setText((m->first));
        action->setData((m->second));
    }
    connect(markerGroup,SIGNAL(triggered(QAction *)),this,SLOT(setMarker(QAction *)));
    /*}}}*/


    /*{{{set curve marker size action*/
    QList< QPair<QString,int> > markerSize;
    markerSize.append(qMakePair(tr("2"),2));
    markerSize.append(qMakePair(tr("4"),4));
    markerSize.append(qMakePair(tr("5"),5));
    markerSize.append(qMakePair(tr("6"),6));
    markerSize.append(qMakePair(tr("7"),7));
    markerSize.append(qMakePair(tr("8"),8));
    markerSize.append(qMakePair(tr("10"),10));
    markerSize.append(qMakePair(tr("12"),12));
    markerSize.append(qMakePair(tr("18"),18));
    markerSize.append(qMakePair(tr("24"),24));
    markerSize.append(qMakePair(tr("48"),48));

    markerSizeGroup = new QActionGroup(this);
    QList <QPair<QString,int> >::iterator t;
    for(t = markerSize.begin(); t < markerSize.end(); t++)
    {
        action = new QAction(markerSizeGroup);
        action->setText((t->first));
        action->setData((t->second));
    }
    connect(markerSizeGroup,SIGNAL(triggered(QAction *)),this,SLOT(setMarkerSize(QAction *)));
    /*}}}*/


    prop = new QAction(tr("Properties..."),this);
    prop->setStatusTip("set curve properties");
    connect(prop,SIGNAL(triggered()),this,SLOT(setProperty()));

}

void iCurve::setColor()
{
    QwtPlotCurve *pCurve = pCanvasPicker->getCurve();
    if(NULL == pCurve)
        return ;

    QColor color = QColorDialog::getColor(Qt::white,this);
    if(!color.isValid())
        return;

    QPen pen = pCurve->pen();
    pen.setColor(color);
    pCurve->setPen(pen);
    const QwtSymbol *symPrev = pCurve->symbol();
    const QwtSymbol *symbol = new QwtSymbol(symPrev->style(), QBrush(color),pen,symPrev->size());
    pCurve->setSymbol(symbol);

    plot->canvas()->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
    plot->replot();
    plot->canvas()->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);

}

void iCurve::setWidth(QAction *action)
{
    bool ok = false;
    int width = 0;	
    QwtPlotCurve *pCurve = NULL;

    pCurve = pCanvasPicker->getCurve();
    if(NULL == pCurve)
        return ;

    QPen pen = pCurve->pen();
    width = action->data().toInt(&ok);
    pen.setWidth(width);
    pCurve->setPen(pen);

    action->setCheckable(true);
    action->setChecked(true);

    plot->canvas()->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
    plot->replot();
    plot->canvas()->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
}

void iCurve::setStyle(QAction *action)
{
    QwtPlotCurve *pCurve = pCanvasPicker->getCurve();
    if(NULL == pCurve)
        return ;

    bool ok;
    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(action->data().toInt(&ok));
    QPen pen = pCurve->pen();
    pen.setStyle( penStyle);
    pCurve->setPen(pen);

    action->setCheckable(true);
    action->setChecked(true);

    plot->canvas()->setPaintAttribute(QwtPlotCanvas::ImmediatePaint,true);
    plot->replot();
    plot->canvas()->setPaintAttribute(QwtPlotCanvas::ImmediatePaint,false);

}

void iCurve::setMarker(QAction *action)
{
    QwtPlotCurve *pCurve = pCanvasPicker->getCurve();
    if(NULL == pCurve)
        return ;

    bool ok;
    QwtSymbol::Style symStyle = static_cast<QwtSymbol::Style>(action->data().toInt(&ok));
    QColor curveColor = pCurve->pen().color();
    const QwtSymbol *symPrev = pCurve->symbol();
    const QwtSymbol *symbol = new QwtSymbol(symStyle, QBrush(curveColor),QPen(curveColor, 2 ),symPrev->size());
    pCurve->setSymbol(symbol);

    action->setCheckable(true);
    action->setChecked(true);

    plot->canvas()->setPaintAttribute(QwtPlotCanvas::ImmediatePaint,true);
    plot->replot();
    plot->canvas()->setPaintAttribute(QwtPlotCanvas::ImmediatePaint,false);
}

void iCurve::setMarkerSize(QAction *action)
{

    QwtPlotCurve *pCurve = pCanvasPicker->getCurve();
    if(NULL == pCurve)
        return ;

    bool ok;
    int w = action->data().toInt(&ok);
    const QwtSymbol *symPrev = pCurve->symbol();
    QwtSymbol::Style symStyle = symPrev->style();
    QColor curveColor = pCurve->pen().color();
    const QwtSymbol *symbol = new QwtSymbol(symStyle, QBrush(curveColor), \
            QPen( curveColor, 2),QSize(w,w));
    pCurve->setSymbol(symbol);

    action->setCheckable(true);
    action->setChecked(true);

    plot->canvas()->setPaintAttribute(QwtPlotCanvas::ImmediatePaint,true);
    plot->replot();
    plot->canvas()->setPaintAttribute(QwtPlotCanvas::ImmediatePaint,false);
}

void iCurve::setProperty()
{
    propDiag = new CurvePropertyDialog(this);
    if(NULL == prop)
        return ;

    propDiag->resize(400,150);
    propDiag->show();

    return;
}

void iCurve::delCurve()
{
    QwtPlotCurve *pCurve = pCanvasPicker->getCurve();
    if(NULL == pCurve)
        return ;

    pCurve->detach();
    pCanvasPicker->delMarker();
    plot->canvas()->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,true);
    plot->replot();
    plot->canvas()->setPaintAttribute( QwtPlotCanvas::ImmediatePaint,false);
    delete pCurve;
    pCanvasPicker->clearCurve();
}


QwtPlot* iCurve::getPlot()
{
    return plot;
}

CanvasPicker* iCurve::getPicker()
{
    return pCanvasPicker;
}

CurvePropertyDialog* iCurve::getPropertyDialog()
{
    return propDiag;

}

void iCurve::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open file..."),
            fileInfo.absolutePath(),tr("Text files (*.txt);;All Files (*)"));
    if(!fileName.isEmpty())
    {
        fileInfo = QFileInfo(fileName);

        loadData(fileName);

    }
}


bool iCurve::loadData(const QString &vFile)
{
    QFile file(vFile);

    if(!file.exists())
    {
        return false;
    }

    if(!file.open(QFile::ReadOnly ))
    {
        return false;
    }

    qint32 n = 0;
    qint32 i=0;
    qint32 tone = 0;
    QPolygonF points;
    QPointF pointF;
    bool ok = true;
    float point;

    QTextStream dataTextStream(&file);
    tone = 0;
    while(!dataTextStream.atEnd())
    {

        QString dataStr = dataTextStream.readLine();
        QStringList dataStrList = dataStr.split(QRegExp("[:\\s]"),QString::SkipEmptyParts);
        n = dataStrList.count();
        if(n<=0)
            continue;

        if(!dataStrList.at(0).at(0).isDigit())
            continue;

        for(i=1; i<n; i++)
        {
            point = dataStrList.at(i).toFloat(&ok);
            if(true == ok)
            {
                tone++;
                pointF.setX(tone);
                pointF.setY(point);
                points.append(pointF);
            }
        }
    }


    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setPen( QPen( Qt::blue, 1 ) );
    curve->setSamples( points );

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::NoSymbol,
            QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );

    QString curveName = fileInfo.baseName();		
    curve->setTitle(curveName);
    curve->attach( plot );

    plot->setAxisScale( QwtPlot::yLeft, -150.0, 150.0 );
    plot->setAxisScale( QwtPlot::xBottom, 0.0, tone );
    plot->replot();

    file.close();
    return true;

}

void iCurve::saveAs()
{
    QwtPlotRenderer renderer;
    renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground);
    renderer.setLayoutFlag(QwtPlotRenderer::KeepFrames);
    renderer.exportTo(plot,plot->title().text() + ".pdf");
}

void iCurve::editTitle()
{

    EditPlotDialog *editPlot = new EditPlotDialog(this);
    editPlot->resize(400,200);
    editPlot->show();
}


void iCurve::about()
{
    QDialog *dialog = new QDialog(this);
    Ui::Dialog about;
    about.setupUi(dialog);
    dialog->show();
}

void iCurve::contextMenuEvent ( QContextMenuEvent * event )
{
    if(NULL != pCanvasPicker->getCurve())
        mainPopMenu->exec(event->globalPos());
}

void iCurve::paintEvent(QPaintEvent *event)
{

}

bool iCurve::eventFilter ( QObject* watched, QEvent * event )
{

    return QMainWindow::eventFilter(watched, event);

}

void iCurve::mouseDoubleClickEvent ( QMouseEvent * event )
{

}


void iCurve::mousePressEvent ( QMouseEvent * event )
{

}

