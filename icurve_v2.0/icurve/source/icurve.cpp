
#include <Qt>
#include <QtGui>
#include <QDialog>  
#include <QMessageBox>
#include <QDir>
#include <QIcon>
#include <QPair>
#include <QList>
#include <QSize>
#include <QRegExp>
#include "icurve.h"

#define MAX_NUM_DIGITS_PERLINE    11  /*including tone index at head of the line*/
#define PLOT_DATA_START_POS       1


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


ICU_RET_STATUS icurve::loadData(const QString &filename)
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
    
}


ICU_RET_STATUS icurve::analyzeData(QFile file)
{
    qint32 cout = 0;
    qint32 i=0;
    qint32 tone = 0;
    QPolygonF points;
    QPointF pointF;
    bool ok = true;
    float point;

    QTextStream dataTextStream(&file);
    tone = 0;
    bool isCmdStart = false;
    qint16  line = 0;
    QRegExp regExp; 
    Command cmd;
    QStringList cmdFamily = cmd.getFamily();
    while(!dataTextStream.atEnd())
    {
        QString dataLine = dataTextStream.readLine();
        if(false == isCmdStart)
        {
            for(i = 0; i< cmdFamily.count(); i++)
            {
                qint16 pos = regExp.indexIn(dataLine);
                regExp.setPattern(cmdFamily.value(i));
                if(regExp.captureCount() > 0)/*try to get param of command*/
                {
                    QString pattern(cmdFamily.value(i) + "[0-9]+" + "[0-1]");		  
                    regExp.setPattern(pattern);
                    if(regExp.captureCount() > 0)
                    {
                        isCmdStart = true;
                        cmd.setName(regExp.cap(0));  

                        QString line(regExp.cap(1));
                        cmd.setLineId(line.toInt(&ok));

                        QString dir(regExp.cap(2));
                        cmd.setDirection(dir.toInt(&ok));
                    }
                }
            }

            if(false == isCmdStart)
                cmd.setName("NULL");
        }
        else 
        {
           if(ICU_PLOT_DATA_FORMAT_ERROR == assembleData(dataLine,&cmd))
           {
               QMessageBox msgBox;
               QString info;

               info = "data format error at line" + QString::number(line) + ",please repair.";
               msgBox.setText(info);
               msgBox.exec();

               return ICU_PLOT_DATA_FORMAT_ERROR; 
           }
        }

        line++;
    }

}

ICU_RET_STATUS icurve::assembleData(QString dataLine, Command *cmd)
{
    QRegExp regExp(); 
    QString pattern("\\s:\\s]");		  

    qint16 pos = regExp.indexIn(dataLine);
    regExp.setPattern(pattern);

    if(regExp.captureCount() <= 0)
        return ICU_PLOT_DATA_FORMAT_ERROR;

    QStringList digList = dataLine.split(regExp, QString::SkipEmptyParts);
    qint16 digCount = digList.count();

    if(MAX_NUM_DIGITS_PERLINE != digCount)
    {
        return ICU_PLOT_DATA_FORMAT_ERROR;
    }

    if(!digList.at(0).at(0).isDigit())
    {
        return ICU_PLOT_DATA_FORMAT_ERROR;
    }
    
	bool ok = false;
    qint16 toneIndex = digList.at(0).toInt(&ok);
    if(false == ok)
        return ICU_PLOT_DATA_FORMAT_ERROR;

    QStringList<QPointF> points; 
    QPointF              point;
    qint16               tone = command.data.count();
    for(qint16 i = PLOT_DATA_START_POS; i < digCount; i++)
    {
        qreal dataItem = digList.at(i).toFloat(&ok);
        if(false == ok)
            return ICU_PLOT_DATA_FORMAT_ERROR;

        tone++;
        pointF.setX(tone);
        pointF.setY(dataItem);
        points.append(pointF);
    }

    command.data.append(points);
    return ICU_OK;
}




