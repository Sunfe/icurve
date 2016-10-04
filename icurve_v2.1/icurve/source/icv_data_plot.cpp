#include <QtCore>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QToolBar>
#include <QWhatsThis>
#include <QGridLayout>
#include <QPlainTextEdit>
#include "icv_data_plot.h"


IcvDataPlotDialog::IcvDataPlotDialog(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(700,500);

    QToolBar *toolBar = new QToolBar(this);
    toolBar->setAllowedAreas( Qt::TopToolBarArea | Qt::BottomToolBarArea );
    toolBar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    plotAction  = new QAction(QPixmap(":/icurve/images/draw.png"), "Plot", toolBar );
    clearAction = new QAction(QPixmap(":/icurve/images/clear.png"), "Clear", toolBar );
    saveAction  = new QAction(QPixmap(":/icurve/images/save_data.png"), "Save", toolBar );

    toolBar->addAction( plotAction );
    toolBar->addAction( clearAction );
    toolBar->addAction( saveAction );
    toolBar->setIconSize( QSize( 22, 22 ) );

    QPlainTextEdit *plainTextEdit = new QPlainTextEdit(this);

    QGridLayout *laygout = new QGridLayout(this);
    laygout->addWidget(toolBar,       0, 0, 1, 1);
    laygout->addWidget(plainTextEdit, 1, 0, 1, 1);

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
    return plainTextEdit->toPlainText();
} 


void IcvDataPlotDialog::processClickEvent()
{
 if(sender() == plotAction)
    {
        if(plainTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,tr("Warning"), tr("No input!"), QMessageBox::Close);
            return ;
        }
        emit sigPlotBlockData(plainTextEdit->toPlainText());
    }
    else if(sender() == saveAction)
    {
        if(plainTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,tr("Warning"), tr("No input!"), QMessageBox::Close);
            return ;
        }
        saveBlockData();
    }
    else if(sender() == clearAction)
    {
        plainTextEdit->clear();
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
        stream << plainTextEdit->toPlainText() << endl;    
        stream.flush();    
        file.close();    
    }

    return;
}


