
#include <Qt>
#include <QtGui>
#include <QDialog>  
#include <QMessageBox>
#include <QDir>
#include <QIcon>
#include <QPair>
#include <QList>
#include <QSize>
#include "icurve.h"

icurve::icurve(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);

    initMainWinStyle(this);
    plot = new QwtPlot();
    initMainPlotter(plot);

    setCentralWidget(plot);

    /*signals and slots*/
    connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));

}

icurve::~icurve()
{

}


void icurve::initMainWinStyle(QMainWindow *self)
{
    self->setWindowTitle("iCurve");
    self->setWindowIcon(QIcon(":/images/iCurve.ico"));
    self->setContentsMargins(0,0,0,0);
        
    QPalette mainWinPalette;
    mainWinPalette.setColor(QPalette::Background,Qt::lightGray);
    self->setPalette(mainWinPalette);
}


void icurve::initMainPlotter(QWidget *plotWidget)
{
    QwtPlot *plot = static_cast<QwtPlot*>(plotWidget);
    plot->setTitle( "unamed" );
    
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, -200.0, 200.0 );
    plot->setAxisScale( QwtPlot::xBottom, 0, 5000 );
    
    plot->setAxisLabelAlignment(QwtPlot::xBottom,Qt::AlignLeft);
    plot->setAxisLabelAlignment(QwtPlot::yLeft,Qt::AlignTop);
    
    plot->plotLayout()->setAlignCanvasToScales( false );
    plot->plotLayout()->setCanvasMargin(0);

    QwtPlotLegendItem *le= new QwtPlotLegendItem();
    le->attach(plot);

    grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::DashLine));
    grid->setMinorPen(QPen(Qt::DashLine));  
    grid->attach( plot );

    ( void ) new QwtPlotPanner( plot->canvas());
    ( void ) new QwtPlotMagnifier(plot->canvas());
    
    return ;
}


void icurve::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                           tr("Open file..."),
                           fileInfo.absolutePath(),
                           tr("Text files (*.txt);;All Files (*)"));
    
    if(!fileName.isEmpty())
    {
        fileInfo = QFileInfo(fileName);
        //loadData(fileName);
    }   

    return ;
}


RET_STATUS icurve::loadData(const QString &filename)
{
    QFile file(filename);

    if(!file.exists())
    {
        return SUCCESS;
    }

    if(!file.open(QFile::ReadOnly ))
    {
        return ERROR;
    }

#if 0
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
    #endif
    
}


