#include <QtCore>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include "icv_data_plot.h"

IcvDataPlotDialog::IcvDataPlotDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);

    connect(ui.plotButton,  SIGNAL(clicked()), this, SLOT(processClickEvent()));
    connect(ui.saveButton,  SIGNAL(clicked()), this, SLOT(processClickEvent()));
    connect(ui.closeButton, SIGNAL(clicked()), this, SLOT(processClickEvent()));
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
    if(sender() == ui.plotButton)
    {
        if(ui.plainTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,tr("Warning"), tr("No input!"), QMessageBox::Close);
            return ;
        }
        emit sigPlotBlockData(ui.plainTextEdit->toPlainText());
    }
    else if(sender() == ui.saveButton)
    {
        if(ui.plainTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(this,tr("Warning"), tr("No input!"), QMessageBox::Close);
            return ;
        }
        saveBlockData();
    }
    else if(sender() == ui.closeButton)
    {
        close();
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


