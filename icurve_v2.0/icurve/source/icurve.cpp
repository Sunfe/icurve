
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

#include <QDebug>

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
        loadData(fileName);
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


    if(ICU_OK != analyzeData(file))
    {
        return ICU_PLOT_DATA_FORMAT_ERROR;
    }

    return ICU_OK;
}


ICU_RET_STATUS icurve::analyzeData(QFile &file)
{
    qint32 cout     = 0;
    bool ok         = true;
    bool isCmdStart = false;
    qint16  line    = 0;
    QRegExp regExp; 
    Command cmd;
    Command prevCmd;

    QTextStream dataTextStream(&file);
    QStringList cmdFamily = cmd.getFamily();
    while(!dataTextStream.atEnd())
    {
        line++;
        QString dataLine = dataTextStream.readLine();

        qint16 i = 0;
        qint16 pos = 0;
        QString curCmd("NULL");
        for(i = 0; i< cmdFamily.count(); i++)
        {
            regExp.setPattern(cmdFamily.value(i));
            pos = regExp.indexIn(dataLine);

            if(-1 != pos)
            {
                curCmd = cmdFamily.value(i);
                break;
            }

        }

        if("NULL" != curCmd) /*try to get parameters of command*/
        {

            QString pattern(curCmd + "\\s+([0-9]|1[0-9])\\s+([0-1])");		
            regExp.setPattern(pattern);
            pos = regExp.indexIn(dataLine);
            if(-1 != pos)
            {
                /*if a new command found,and the last command is not empty,
                  set the last command complete 
                 */
                prevCmd = cmd;

                cmd.reset();
                cmd.setName(regExp.capturedTexts().at(0));  

                QString port(regExp.capturedTexts().at(1));
                cmd.setLineId(port.toInt(&ok));

                QString dir(regExp.capturedTexts().at(2));
                cmd.setDirection(dir.toInt(&ok));

                isCmdStart = true;
            }

        }


        if(true == isCmdStart)
        {
            if(prevCmd.getData().count() > 0)      
            {
                plotData.push_back(prevCmd);   
                prevCmd.reset();
            }

            regExp.setPattern("\\s+:\\s+");
            if(-1 == regExp.indexIn(dataLine))
            {
                continue;
            }

            qint16 ret = assembleData(dataLine,&cmd);
            if(ret == ICU_PLOT_DATA_FORMAT_ERROR)
            {
                QString error = file.fileName() + " at line " + QString::number(line) \
                                + ":data format incorrect.";
                QMessageBox::critical(this,"ERROR",error);

                return ICU_PLOT_DATA_FORMAT_ERROR; 
            }
        }
    }

    /*no more new command found when at file end, save the current data*/
    if(cmd.getData().count() > 0)      
        plotData.push_back(cmd);   

    QString error = QString::number(plotData.count());
    QMessageBox::critical(this,"ERROR",error);

    return ICU_OK; 
}


ICU_RET_STATUS icurve::assembleData(QString dataLine, Command *cmd)
{
    QStringList splitList;
    QStringList digList;


    splitList = dataLine.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if(!splitList.contains(":") )  /*only ":"*/
        return ICU_PLOT_DATA_FORMAT_ERROR;

    digList = splitList.filter(QRegExp("^\\d+$|^\\d+\\.\\d+$"));


    if(MAX_NUM_DIGITS_PERLINE != digList.count())
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

    QList<QPointF> points; 
    QPointF        point;
    qint16         tone = cmd->getData().count();
    for(qint16 i = PLOT_DATA_START_POS; i < digList.count(); i++)
    {
        qreal dataItem = digList.at(i).toFloat(&ok);
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




