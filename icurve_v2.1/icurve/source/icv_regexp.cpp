#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QPair>
#include <QDebug>
#include "icv_regexp.h"
#include "icv_pattern_table.h"
#include "icv_table_widget.h"

extern QString icvCmdTitlePatternTbl[ICV_MAX_TITLE_PATTERN_NUM];
extern QString icvCmdDataPatternTbl[ICV_MAX_DATA_PATTERN_NUM][2];
extern QString icvCmdSpecCharTbl[ICV_MAX_DATA_PATTERN_NUM][3];

IcvRegExp::IcvRegExp(QWidget *parent,Qt::WindowFlags flag)
    : QDialog(parent,flag)
{
    setupUi(this);    
    /* title patterns */
    tableWidgetTitle = new IcvTableWidget(ICV_MAX_TITLE_PATTERN_NUM, 2, tabTitlePattern);
    tableWidgetTitle->setGeometry(QRect(10, 10, 740, 430));
    tableWidgetTitle->setHorizontalHeaderLabels(QStringList("patterns"));
    tableWidgetTitle->setColumnWidth(0, 50);
    tableWidgetTitle->setResizeMode(1, QHeaderView::Stretch);
    tableWidgetTitle->setHeaderVisible(false, false);
    for(qint16 nr = 0; nr < ICV_MAX_TITLE_PATTERN_NUM; nr++)
    {
        if(!icvCmdTitlePatternTbl[nr].isEmpty())
            tableWidgetTitle->setItem(nr, 0, new QTableWidgetItem(QString::number(nr))); 
        tableWidgetTitle->setItem(nr, 1, new QTableWidgetItem(icvCmdTitlePatternTbl[nr]));  
    }

    /* data patterns */
    tableWidgetData = new IcvTableWidget(ICV_MAX_DATA_PATTERN_NUM, 3, tabDataPattern);
    tableWidgetData->setGeometry(QRect(10, 10, 740, 430));
    tableWidgetData->setHorizontalHeaderLabels(QStringList("patterns"));  
    tableWidgetData->setColumnWidth(0, 50);
    tableWidgetData->setResizeMode(1, QHeaderView::ResizeToContents);
    tableWidgetData->setResizeMode(2, QHeaderView::ResizeToContents);
    tableWidgetData->setHeaderVisible(false, false);
    for(qint16 nr = 0; nr < ICV_MAX_DATA_PATTERN_NUM; nr++)
    {
        if(!icvCmdDataPatternTbl[nr][0].isEmpty())
            tableWidgetData->setItem(nr, 0, new QTableWidgetItem(QString::number(nr))); 
        tableWidgetData->setItem(nr,1,new QTableWidgetItem(icvCmdDataPatternTbl[nr][0]));  
        tableWidgetData->setItem(nr,2,new QTableWidgetItem(icvCmdDataPatternTbl[nr][1]));  
    }

    /* spectial character replacement */
    tableWidgetSpec = new IcvTableWidget(ICV_MAX_DATA_PATTERN_NUM, 4, tabSpecChar);
    tableWidgetSpec->setGeometry(QRect(10, 10, 740, 430));
    tableWidgetSpec->setHorizontalHeaderLabels(QStringList("patterns"));  
    tableWidgetSpec->setColumnWidth(0, 50);
    tableWidgetSpec->setResizeMode(1, QHeaderView::ResizeToContents);
    tableWidgetSpec->setColumnWidth(2, 100);
    tableWidgetSpec->setColumnWidth(3, 100);
    tableWidgetSpec->setHeaderVisible(false, false);

    for(qint16 nr = 0; nr < ICV_MAX_DATA_PATTERN_NUM; nr++)
    {
        if(!icvCmdSpecCharTbl[nr][0].isEmpty())
            tableWidgetSpec->setItem(nr, 0, new QTableWidgetItem(QString::number(nr))); 
        tableWidgetSpec->setItem(nr,1,new QTableWidgetItem(icvCmdSpecCharTbl[nr][0]));  
        tableWidgetSpec->setItem(nr,2,new QTableWidgetItem(icvCmdSpecCharTbl[nr][1]));  
        tableWidgetSpec->setItem(nr,3,new QTableWidgetItem(icvCmdSpecCharTbl[nr][2]));  
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

