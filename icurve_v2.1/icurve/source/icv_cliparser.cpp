#include <QtGlobal>
#include <Qt>
#include <QDebug>
#include <QTextEdit>
#include <QSplitter>
#include <QTextStream>
#include <QString>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include "icv_cliparser.h"
#include "icurve_common.h"

#define ICV_DATA_SET_MODE_AUTO        (0)
#define ICV_DATA_SET_MODE_HALF_HALF   (1)
#define ICV_DATA_SET_MODE_1_1         (2)
#define ICV_DATA_SET_MODE_1_2         (3)
#define ICV_DATA_SET_MODE_2_1         (4)
#define ICV_DATA_SET_MODE_2_2         (5)

IcvCliParserDialog::IcvCliParserDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    /* toolbar setup */
    QToolBar *toolBar = new QToolBar(this);
    toolBar->setAllowedAreas( Qt::TopToolBarArea | Qt::BottomToolBarArea );
    toolBar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    plotAction   = new QAction(QPixmap(":/icurve/images/draw.png"), "Plot", toolBar );
    clearAction  = new QAction(QPixmap(":/icurve/images/clear.png"), "Clear", toolBar );
    saveAction   = new QAction(QPixmap(":/icurve/images/save_data.png"), "Save", toolBar );
    exportAction = new QAction(QPixmap(":/icurve/images/export_data.png"), "Export", toolBar );
    toolBar->addAction(plotAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(exportAction);
    toolBar->addAction(clearAction);
    toolBar->setIconSize(QSize(22, 22));
    ui.layoutToolbar->addWidget(toolBar);
    /* editor setup */
    orig = new QTextEdit(this); 
    target = new QTextEdit(this);
    QSplitter *splitter = new QSplitter(Qt::Horizontal); 
    splitter->addWidget(orig);
    splitter->addWidget(target);
    ui.layoutSplitter->addWidget(splitter);
    /* default */
    ui.comboBoxSeg->setCurrentIndex(ICV_DATA_SET_MODE_AUTO);
    orig->setFocus();
    target->setReadOnly(true);
    /* slots */
    connect(ui.pushButtonConvert, SIGNAL(clicked(bool)), this, SLOT(parzeHex(bool)));
    connect(ui.comboBoxSeg,       SIGNAL(activated(int)),this, SLOT(activateSegMode(int)));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportData()));
    connect(clearAction,  SIGNAL(triggered()), this, SLOT(clear()));
    connect(saveAction,   SIGNAL(triggered()), this, SLOT(save()));
}

IcvCliParserDialog::~IcvCliParserDialog()
{

}

void IcvCliParserDialog::parzeHex(bool)
{
    if(orig->toPlainText() == "")
    {
        QMessageBox::warning(this,tr("Warning"), tr("No content!"), QMessageBox::Close);
        return;
    }

    QString text = orig->toPlainText();
    QTextStream stream(&text);
    QString output;
    bool ok;
    qint16 segMode = 0;
    qint16 curIndex = 0;
    qint16 delectedCmd = 0;

    curIndex = ui.comboBoxSeg->currentIndex();
    delectedCmd = 0xff;
    QRegExp reg;
    reg.setCaseSensitivity(Qt::CaseInsensitive);
    while(!stream.atEnd())
    {
        QString dataLine = stream.readLine();
        reg.setPattern(QString("Bitload|Qln|SNR|GainAlloc|Hlog|LinImg|LinReal"));
        if(dataLine.contains(reg))
        {
            if(ICV_DATA_SET_MODE_AUTO != curIndex)
            {
                segMode = ui.comboBoxSeg->currentIndex();
                continue;         
            }

            if(dataLine.contains(tr("Qln")))
            {
                segMode = ICV_DATA_SET_MODE_1_1;
                delectedCmd = ICV_CLI_QLN;
            }
            else if(dataLine.contains(tr("SNR")))
            {
                segMode = ICV_DATA_SET_MODE_1_1;
                delectedCmd = ICV_CLI_SNR;
            }
            else if(dataLine.contains(tr("Hlog")))
            {
                segMode = ICV_DATA_SET_MODE_2_2;
                delectedCmd = ICV_CLI_HLOG;
            }
            else if(dataLine.contains(tr("LinImg")))
            {
                segMode = ICV_DATA_SET_MODE_2_2;
                delectedCmd = ICV_CLI_LINIMG;
            }
            else if(dataLine.contains(tr("LinReal")))
            {
                segMode = ICV_DATA_SET_MODE_2_2;
                delectedCmd = ICV_CLI_LINREAL;
            }
            else if(dataLine.contains(tr("Bitload")))
            {
                segMode = ICV_DATA_SET_MODE_HALF_HALF;
                delectedCmd = ICV_CLI_BITLOAD;
            }
            else if(dataLine.contains(tr("GainAlloc")))
            {
                segMode = ICV_DATA_SET_MODE_2_2;
                delectedCmd = ICV_CLI_GAINALLOC;
            }
            output += dataLine + "\n";
        }
        else if(dataLine.contains(QRegExp("^\\s?(\\s+[\\dA-F]{2}){1,16}\\s?$")))
        {
            switch(segMode)
            {
            case ICV_DATA_SET_MODE_1_1:
                output += rfcSeg(fetchHexSegment(dataLine, "1-1"), delectedCmd);
                break;
            case ICV_DATA_SET_MODE_1_2:
                output += fetchHexSegment(dataLine, "1-2");
                break;
            case ICV_DATA_SET_MODE_2_1:
                output += fetchHexSegment(dataLine, "2-1");
                break;
            case ICV_DATA_SET_MODE_2_2:
                output +=  rfcSeg(fetchHexSegment(dataLine, "2-2"), delectedCmd);
                break;
            case ICV_DATA_SET_MODE_HALF_HALF:
                output += rfcSeg(fetchHexSegment(dataLine, "0.5-0.5"),delectedCmd);
                break;
            default:
                break;
            }
        }
        else
        {
            output += dataLine + "\n";
        }
    }

    target->setPlainText(output);
    return;
}

void IcvCliParserDialog::activateSegMode(int index)
{
    if(index != ICV_DATA_SET_MODE_AUTO)
    {
        ui.checkBoxRfc->setCheckState(Qt::Unchecked);
        ui.checkBoxRfc->setEnabled(false);
    }
    else
    {
        ui.checkBoxRfc->setEnabled(true);
        ui.checkBoxRfc->setCheckState(Qt::Checked);
    }
    return;
}

void IcvCliParserDialog::clear()
{
    orig->clear();
    target->clear();
    orig->setFocus();
    return;
}

void IcvCliParserDialog::save()
{
    if(target->toPlainText() == "")
    {
        QMessageBox::warning(this,tr("Warning"), tr("No content!"), QMessageBox::Close);
        return ;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"),"icurve.txt",tr("text files(*.txt);"));
    if (!fileName.isNull())
    {
        QFile file(fileName);  
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {    
            QMessageBox::critical(NULL, "error", "unable to create file!");  
            return;    
        }    
        QTextStream stream(&file);    
        stream << target->toPlainText() << endl;    
        stream.flush();    
        file.close();    
    }
    return;
}

void IcvCliParserDialog::exportData()
{
    if(target->toPlainText() == "")
    {
        QMessageBox::warning(this,tr("Warning"), tr("No content!"), QMessageBox::Close);
        return ;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"),"icurve.csv",tr("text files(*.csv);"));
    if (fileName.isNull())
        return;

    QFile file(fileName);  
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) 
    {    
        QMessageBox::critical(NULL, "error", "unable to create file!");  
        return;    
    }

    QString text = target->toPlainText();
    QTextStream stream(&text);
    QString outTxt;
    while(!stream.atEnd())
    {
        QString dataLine = stream.readLine();
        QStringList dlist = dataLine.split(" ", QString::SkipEmptyParts);
        for(qint16 i = 0; i < dlist.count(); i++)
        {
            outTxt += dlist[i] + ",";
        }
        outTxt += "\n";
    }

    QTextStream out(&file);    
    out << outTxt << endl;    
    out.flush();    
    file.close();   
    QMessageBox::information(NULL, "info", "done!");  
    return;
}

QString IcvCliParserDialog::fetchHexSegment(QString dataLineHex, QString segMode)
{
    QString     out;
    QStringList hexs;
    QStringList seg;
    QString     decim;
    qint16      i  = 0;
    bool        ok = false;
    qint16      firstSegLen  = 0;
    qint16      secondSegLen = 0;

    hexs = dataLineHex.split(" ", QString::SkipEmptyParts);
    seg  = segMode.split(QRegExp("\\s+|,|-"));
    if(seg.count() < 2)
        return "NULL";
    /*half segment */
    if(seg[0] == "0.5" && seg[1] == "0.5")  
    {
        i = 0;
        while(i < hexs.count())
        {
            QString decim_f;
            QString decim_s;
            decim_f.sprintf("%2d", (hexs.at(i).left(1).toInt(&ok,16)));
            decim_s.sprintf("%2d", (hexs.at(i).right(1).toInt(&ok,16)));
            decim = decim_f + " " + decim_s;
            out += decim + " ";
            i++;
        }
        out += "\n";
        return out;
    }
 
    firstSegLen  = seg[0].toInt(&ok,10);
    secondSegLen = seg[1].toInt(&ok,10);
    while(i < hexs.count())
    {
        QString seg;
        qint16  j  = 0;
        while(j < firstSegLen && (i + j < hexs.count()))
        {
            seg += hexs.at(i + j);
            j++;
        }
        decim.sprintf("%6d", seg.toInt(&ok,16));
        out += decim;

        seg = "";
        j   = 0;
        while(j < secondSegLen && (i + j + firstSegLen < hexs.count()))
        {
            seg += hexs.at(i + j + firstSegLen);
            j++;
        }
        decim.sprintf("%6d", seg.toInt(&ok,16));
        out += decim;
        i += firstSegLen + secondSegLen;
    }
    out += "\n";
    return out;
}

QString IcvCliParserDialog::rfcSeg(QString dataLine, qint16 cmd)
{
    if(Qt::Unchecked == ui.checkBoxRfc->checkState())
        return dataLine;

    QStringList seg;
    seg = dataLine.split(" ", QString::SkipEmptyParts);
    if(seg.isEmpty())
        return dataLine;

    QString output;
    for(qint16 i = 0; i < seg.count(); i++)
    {
        bool ok = false;
        float dsegf = 0.0;
        int   dsegi = 0;
        if(ICV_CLI_HLOG == cmd)
        {
            dsegf = seg[i].toFloat(&ok);
            dsegf = RFC_HLOG_CONV(dsegf);
        }
        else if(ICV_CLI_QLN == cmd)
        {
            dsegf = seg[i].toFloat(&ok);
            dsegf = RFC_QLN_CONV(dsegf);
        }
        else if(ICV_CLI_SNR == cmd)
        {
            dsegf = seg[i].toFloat(&ok);
            dsegf = RFC_SNR_CONV(dsegf);
        }
        else if(ICV_CLI_GAINALLOC == cmd)
        {
            dsegf = seg[i].toFloat(&ok);
            dsegf = RFC_GAIN_CONV(dsegf);
        }
        else
        {
            dsegi = seg[i].toInt(&ok);
        }

        QString str;
        if((ICV_CLI_HLOG == cmd)||(ICV_CLI_QLN == cmd)||(ICV_CLI_SNR == cmd)||(ICV_CLI_GAINALLOC == cmd))
            str.sprintf("%6.1f",dsegf);
        else if(ICV_CLI_BITLOAD == cmd)
            str.sprintf("%2d",dsegi);
        else if((ICV_CLI_LINIMG == cmd)||(ICV_CLI_LINREAL == cmd))
            str.sprintf("%6d",dsegi);
        output.append(str + " ");
    }
    output += "\n";
    return output;
}

