#include "icv_table_widget.h"

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

void IcvTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
    popMenu = new QMenu(this);
    popMenu->clear(); 
    QPoint point = event->pos(); 
    QTableWidgetItem *item = this->itemAt(point);
    if(item != NULL)
    {
        popMenu->addAction("copy to excel");
        popMenu->addSeparator();
        popMenu->exec(QCursor::pos());
        event->accept();
    } 
}

