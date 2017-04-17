#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QPair>
#include <QDebug>
#include "icv_regexp.h"
#include "icv_pattern_table.h"

extern QString icvCmdTitlePatternTbl[ICV_MAX_TITLE_PATTERN_NUM];
extern QString icvCmdDataPatternTbl[ICV_MAX_DATA_PATTERN_NUM][2];
extern QString icvCmdSpecCharTbl[ICV_MAX_DATA_PATTERN_NUM][3];

IcvRegExp::IcvRegExp(QWidget *parent,Qt::WindowFlags flag)
    : QDialog(parent,flag)
{
    setupUi(this);    
    /* title patterns */
    tableWidgetTitle = tabRegExp->findChild<QTableWidget *>("tableTitlePattern");
    tableWidgetTitle->setRowCount(ICV_MAX_TITLE_PATTERN_NUM);
    tableWidgetTitle->setColumnCount(1);
    tableWidgetTitle->setHorizontalHeaderLabels(QStringList("patterns"));  
    tableWidgetTitle->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    tableWidgetTitle->horizontalHeader()->setVisible(false);
    tableWidgetTitle->verticalHeader()->setVisible(false);
    tableWidgetTitle->setAlternatingRowColors(true);
    tableWidgetTitle->setStyleSheet("selection-background-color:#63B8FF;selection-color:black;"
                                    "alternate-background-color: rgb(245, 245, 245);");
    tableWidgetTitle->setFont(QFont("Helvetica"));
    for(qint16 nr = 0; nr < ICV_MAX_TITLE_PATTERN_NUM; nr++)
    {
        tableWidgetTitle->setItem(nr, 0, new QTableWidgetItem(icvCmdTitlePatternTbl[nr]));  
    }
    /* data patterns */
    tableWidgetData = tabRegExp->findChild<QTableWidget *>("tableDataPattern");
    tableWidgetData->setRowCount(ICV_MAX_DATA_PATTERN_NUM);
    tableWidgetData->setColumnCount(2);
    tableWidgetData->setHorizontalHeaderLabels(QStringList("command")<<"pattern");  
    tableWidgetData->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
    tableWidgetData->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
    tableWidgetData->horizontalHeader()->setVisible(false);
    tableWidgetData->verticalHeader()->setVisible(false);
    tableWidgetData->setAlternatingRowColors(true);
    tableWidgetData->setStyleSheet("selection-background-color:#63B8FF;selection-color:black;"
        "alternate-background-color: rgb(245, 245, 245);");
    tableWidgetData->setStyleSheet("selection-background-color:#63B8FF; selection-color:black;");
    tableWidgetData->setFont(QFont("Helvetica"));
    for(qint16 nr = 0; nr < ICV_MAX_DATA_PATTERN_NUM; nr++)
    {
        tableWidgetData->setItem(nr,0,new QTableWidgetItem(icvCmdDataPatternTbl[nr][0]));  
        tableWidgetData->setItem(nr,1,new QTableWidgetItem(icvCmdDataPatternTbl[nr][1]));  
    }
    /* spectial character replacement */
    tableWidgetSpec = tabRegExp->findChild<QTableWidget *>("tableSpecChar");
    tableWidgetSpec->setRowCount(ICV_MAX_DATA_PATTERN_NUM);
    tableWidgetSpec->setColumnCount(3);
    tableWidgetSpec->setHorizontalHeaderLabels(QStringList("command")<<"character"<<"replacement");  
    tableWidgetSpec->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
    tableWidgetSpec->horizontalHeader()->setResizeMode(1, QHeaderView::ResizeToContents);
    tableWidgetSpec->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);
    tableWidgetSpec->horizontalHeader()->setVisible(false);
    tableWidgetSpec->verticalHeader()->setVisible(false);
    tableWidgetSpec->setAlternatingRowColors(true);
    tableWidgetSpec->setStyleSheet("selection-background-color:#63B8FF;selection-color:black;"
        "alternate-background-color: rgb(245, 245, 245);");
    tableWidgetSpec->setFont(QFont("Helvetica"));


    for(qint16 nr = 0; nr < ICV_MAX_DATA_PATTERN_NUM; nr++)
    {
        tableWidgetSpec->setItem(nr,0,new QTableWidgetItem(icvCmdSpecCharTbl[nr][0]));  
        tableWidgetSpec->setItem(nr,1,new QTableWidgetItem(icvCmdSpecCharTbl[nr][1]));  
        tableWidgetSpec->setItem(nr,2,new QTableWidgetItem(icvCmdSpecCharTbl[nr][2]));  
    }
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

IcvRegExp::~IcvRegExp()
{

}

void IcvRegExp::accept()
{
    for(qint16 nr = 0; nr < tableWidgetTitle->rowCount(); nr++)
    {
        icvCmdTitlePatternTbl[nr] = tableWidgetTitle->item(nr,0)->text();
    }

    for(qint16 nr = 0; nr < tableWidgetData->rowCount(); nr++)
    {
        icvCmdDataPatternTbl[nr][0] = tableWidgetData->item(nr,0)->text();
        icvCmdDataPatternTbl[nr][1] = tableWidgetData->item(nr,1)->text();
    }

    for(qint16 nr = 0; nr < tableWidgetSpec->rowCount(); nr++)
    {
        icvCmdSpecCharTbl[nr][0] = tableWidgetSpec->item(nr,0)->text();
        icvCmdSpecCharTbl[nr][1] = tableWidgetSpec->item(nr,1)->text();
        icvCmdSpecCharTbl[nr][2] = tableWidgetSpec->item(nr,2)->text();
    }
    return QDialog::accept ();
}

void IcvRegExp::reject()
{
    return QDialog::reject ();
}

