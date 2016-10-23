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
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));
    connect(saveAction,  SIGNAL(triggered()), this, SLOT(save()));
}

IcvCliParserDialog::~IcvCliParserDialog()
{

}

void IcvCliParserDialog::parzeHex(bool)
{
    QString text = orig->toPlainText();
    QTextStream stream(&text);
    QString output;
    bool ok;
    qint16 segMode = 0;
    while(!stream.atEnd())
    {
        QString dataLine = stream.readLine();
        QRegExp reg;
        reg.setPattern(QString("Bitload|Qln|SNR|GainAlloc|Hlog|LinImg|LinReal"));
        reg.setCaseSensitivity(Qt::CaseInsensitive);
        if(dataLine.contains(reg))
        {
            if(ICV_DATA_SET_MODE_AUTO == ui.comboBoxSeg->currentIndex())
            {
                if(dataLine.contains(tr("Bitload")))
                    segMode = ICV_DATA_SET_MODE_HALF_HALF;
                else if(dataLine.contains(QRegExp("Qln|SNR")))
                    segMode = ICV_DATA_SET_MODE_1_1;
                else if(dataLine.contains(QRegExp("GainAlloc|Hlog|LinImg|LinReal")))
                    segMode = ICV_DATA_SET_MODE_2_2;
                else
                    segMode = ICV_DATA_SET_MODE_1_1;
            }
            else
            {
                segMode = ui.comboBoxSeg->currentIndex();
            }
            output += dataLine + "\n";
            continue;
        }

        reg.setPattern(QString("^\\s+(\\s+[\\dA-F]{2}){,16}"));
        reg.setCaseSensitivity(Qt::CaseInsensitive);
        if(!dataLine.contains(reg))
        {
            output += dataLine + "\n";
            continue;
        }
 
        QStringList hexs = dataLine.split(" ", QString::SkipEmptyParts);
        for(qint16 i = 0; i < hexs.count(); i++)
        {
            QString str;
            switch(segMode)
            {
            case ICV_DATA_SET_MODE_1_1:
                {
                    str.sprintf("%3d", hexs.at(i).toInt(&ok,16));
                    break;
                }
            case ICV_DATA_SET_MODE_1_2:
                {
                    QString strf;
                    QString strs;
                    strf.sprintf("%3d", hexs.at(i).toInt(&ok,16));
                    i++;
                    if(i >= hexs.count() || i + 1 >= hexs.count())
                        continue;
                    strs.sprintf("%6d", (hexs.at(i) + hexs.at(i + 1)).toInt(&ok,16));
                    str = strf +" " + strs;
                    i++;
                    break;
                }
            case ICV_DATA_SET_MODE_2_1:
                {
                    QString strf;
                    QString strs;
                    if(i >= hexs.count() || i + 1 >= hexs.count())
                        continue;
                    strf.sprintf("%6d", (hexs.at(i) + hexs.at(i + 1)).toInt(&ok,16));
                    i+=2;
                    if(i >= hexs.count())
                        continue;
                    strs.sprintf("%3d", hexs.at(i).toInt(&ok,16));
                    str = strf + " " + strs;
                    break;
                }
            case ICV_DATA_SET_MODE_2_2:
                {
                    QString strf;
                    QString strs;
                    if(i >= hexs.count() || i + 1 >= hexs.count())
                        continue;
                    strf.sprintf("%6d", (hexs.at(i) + hexs.at(i + 1)).toInt(&ok,16));
                    i+=2;
                    if(i >= hexs.count() || i + 1 >= hexs.count())
                        continue;
                    strs.sprintf("%6d", (hexs.at(i) + hexs.at(i + 1)).toInt(&ok,16));
                    str = strf + " " + strs;
                    i++;
                    break;
                }
            case ICV_DATA_SET_MODE_HALF_HALF:
                {
                    QString strf;
                    QString strs;
                    strf.sprintf("%2d", (hexs.at(i).left(1).toInt(&ok,16)));
                    strs.sprintf("%2d", (hexs.at(i).right(1).toInt(&ok,16)));
                    str = strf + " " + strs;
                    break;
                }
            default:
                break;
            }
            output += str + " ";
        }
        output += "\n";
    }

    target->setPlainText(output);
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

