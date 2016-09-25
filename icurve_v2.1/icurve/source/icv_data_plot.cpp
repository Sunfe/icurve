#include <QtCore>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QToolBar>
#include "icv_data_plot.h"
#include "start.xpm"
#include "clear.xpm"
#include <QWhatsThis>

IcvDataPlotDialog::IcvDataPlotDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    ui.plainTextEdit->setFocus();
    qint16 width  = geometry().width();
    qint16 height = geometry().height();
    setFixedSize(width,height);
    setWindowTitle("block data plot");

    QToolBar *toolBar = new QToolBar(this);
    toolBar->setAllowedAreas( Qt::TopToolBarArea | Qt::BottomToolBarArea );
    toolBar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    plotAction  = new QAction( QPixmap(":/icurve/images/draw.png"), "Plot", toolBar );
    clearAction = new QAction( QPixmap(":/icurve/images/clear.png"), "Clear", toolBar );
    saveAction  = new QAction( QPixmap(":/icurve/images/save_data.png"), "Save", toolBar );

    toolBar->addAction( plotAction );
    toolBar->addAction( clearAction );
    toolBar->addAction( saveAction );
    toolBar->setIconSize( QSize( 22, 22 ) );
    ui.toolbarLayout->addWidget(toolBar);

    connect(plotAction,   SIGNAL(triggered()), this, SLOT(processClickEvent()));
    connect(clearAction,  SIGNAL(triggered()), this, SLOT(processClickEvent()));
    connect(saveAction,   SIGNAL(triggered()), this, SLOT(processClickEvent()));
    connect(this, SIGNAL(sigPlotBlockData(QString)), parent, SLOT(plotBlockData(QString)));

}


IcvDataPlotDialog::~IcvDataPlotDialog()
{

}


QString IcvDataPlotDialog::getDataSting()
{
    return ui.plainTextEdit->toPlainText();
} 


void IcvDataPlotDialog::processClickEvent()
{
 if(sender() == plotAction)
    {
        if(ui.plainTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,tr("Warning"), tr("No input!"), QMessageBox::Close);
            return ;
        }
        emit sigPlotBlockData(ui.plainTextEdit->toPlainText());
    }
    else if(sender() == saveAction)
    {
        if(ui.plainTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,tr("Warning"), tr("No input!"), QMessageBox::Close);
            return ;
        }
        saveBlockData();
    }
    else if(sender() == clearAction)
    {
        ui.plainTextEdit->clear();
    }

    return;
} 


void IcvDataPlotDialog::saveBlockData()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"),
        "unnamed.txt",
        tr("text files(*.txt);"));

    if (!fileName.isNull())
    {

        QFile file(fileName);  
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {    
            QMessageBox::critical(NULL, "error", "unable to create file!");  
            return;    
        }    

        QTextStream stream(&file);    
        stream << ui.plainTextEdit->toPlainText() << endl;    
        stream.flush();    
        file.close();    
    }

    return;
}


