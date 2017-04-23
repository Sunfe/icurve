#include <iostream>     
#include <algorithm>
#include <QtDebug>
#include <QClipboard>
#include <QApplication>
#include "icv_table_widget.h"
#include "icv_pattern_table.h"

IcvTableWidget::IcvTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    setAlternatingRowColors(true);
    setStyleSheet("selection-background-color:#63B8FF;selection-color:black;"
        "alternate-background-color: rgb(245, 245, 245);"
        "QHeaderView::section, QTableCornerButton::section {"
        "padding: 1px;border: none;"
        "border-bottom: 1px solid rgb(160, 160, 160);"
        "border-right: 1px solid rgb(160, 160, 160);"
        "border-bottom: 1px solid gray;"
        "background-color: qlineargradient(spread:reflect,x1:0, y1:0, x2:0, y2:1,"
        "stop:0 rgba(255, 255, 255, 255), stop:1 rgba(164, 164, 164, 255));}");
    setFont(QFont("Helvetica"));

    popMenu = new QMenu(this);
    copyAct = new QAction(this);
    copyAct->setText(QString("copy to excel"));
    popMenu->addAction(copyAct);
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copyToExcel()));
    connect(this, SIGNAL(cellEntered(int row, int column)), this, SLOT(appendCellText(int row, int column)));
}

 IcvTableWidget::IcvTableWidget(int rows, int columns, QWidget * parent)
      : QTableWidget(rows, columns, parent)
 {
     setAlternatingRowColors(true);
     setStyleSheet("selection-background-color:#63B8FF;selection-color:black;"
         "alternate-background-color: rgb(245, 245, 245);"
         "QHeaderView::section, QTableCornerButton::section {"
         "padding: 1px;border: none;"
         "border-bottom: 1px solid rgb(160, 160, 160);"
         "border-right: 1px solid rgb(160, 160, 160);"
         "border-bottom: 1px solid gray;"
         "background-color: qlineargradient(spread:reflect,x1:0, y1:0, x2:0, y2:1,"
         "stop:0 rgba(255, 255, 255, 255), stop:1 rgba(164, 164, 164, 255));}");
     setFont(QFont("Helvetica"));

     popMenu = new QMenu(this);
     copyAct = new QAction(this);
     copyAct->setText(QString("copy to excel"));
     popMenu->addAction(copyAct);
     connect(copyAct, SIGNAL(triggered()), this, SLOT(copyToExcel()));
     connect(this, SIGNAL(cellEntered(int, int)), this, SLOT(appendCellText(int, int)));
 }

IcvTableWidget::~IcvTableWidget()
{

}

void IcvTableWidget::setTableSize(int rows, int columns)
{
    setRowCount(rows);
    setColumnCount(columns);
    return;
}

void IcvTableWidget::setHeaderVisible(bool horVisible, bool verVisible)
{
    horizontalHeader()->setVisible(horVisible);
    verticalHeader()->setVisible(verVisible);
    return;
}

void IcvTableWidget::setResizeMode(int logicalIndex,  QHeaderView::ResizeMode mode)
{
    horizontalHeader()->setResizeMode(logicalIndex, mode);
    return;
}

void IcvTableWidget::appendCellText(int row, int column)
{
    /* for further function */
    return;
}

void IcvTableWidget::copyToExcel()
{
    QString cellText[ICV_MAX_TBLWGT_ROW][ICV_MAX_TBLWGT_COL];
    bool    cellSelect[ICV_MAX_TBLWGT_ROW][ICV_MAX_TBLWGT_COL];
    int row     = 0;
    int column  = 0;

    memset(cellSelect, 0, sizeof cellSelect);
    QList<QTableWidgetItem *> cellItems = selectedItems();
    for(qint16 cnt = 0; cnt < cellItems.count(); cnt++)
    {
        row    = cellItems.at(cnt)->row();
        column = cellItems.at(cnt)->column();
        if(-1 == row || -1 == column)
            continue;
        cellText[row][column]   = cellItems.at(cnt)->text();
        cellSelect[row][column] = true;
    }

    QString excelFormText;
    excelFormText += "<table border='1'>";
    for(qint16 rn = 0; rn < ICV_MAX_TBLWGT_ROW; rn++)
    {
        bool isNewRowFond = false;
        for(qint16 cn = 0; cn < ICV_MAX_TBLWGT_COL; cn++)
        {
            if(cellSelect[rn][cn]) /* find a new row */
            {
                isNewRowFond = true;
                excelFormText += "<tr>";
                break;
            }
        }
        /* get data in the new row */
        for(qint16 cn = 0; cn < ICV_MAX_TBLWGT_COL && (cellSelect[rn][cn]); cn++)
        {
            excelFormText += "<td style='vnd.ms-excel.numberformat:@'>";
            excelFormText += cellText[rn][cn];
            excelFormText += "</td>";
        }
        if(isNewRowFond)
            excelFormText += "</tr>";
    }
    excelFormText += "</table> ";

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(excelFormText);
    return;
}

void IcvTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint point = event->pos(); 
    QTableWidgetItem *item = this->itemAt(point);
    if(item != NULL)
    {   
        popMenu->exec(QCursor::pos());
        event->accept();
    } 
    return QWidget::contextMenuEvent(event);
}

