#include "icv_table_view.h"

IcvTableView::IcvTableView(QWidget *parent)
    : QTableView(parent)
{
    setStyleSheet("selection-background-color:#63B8FF;selection-color:black;"
        "alternate-background-color: rgb(245, 245, 245);"
        "QHeaderView::section, QTableCornerButton::section {"
        "padding: 1px;"
        "border: none;"
        "border-bottom: 1px solid rgb(160, 160, 160);"
        "border-right: 1px solid rgb(160, 160, 160);"
        "border-bottom: 1px solid gray;"
        "background-color: qlineargradient(spread:reflect, "
        "x1:0, y1:0, x2:0, y2:1, "
        "stop:0 rgba(255, 255, 255, 255)," 
        "stop:1 rgba(164, 164, 164, 255));"
        "}");
    setFont(QFont("Helvetica"));
    setFocusPolicy(Qt::NoFocus);
    verticalHeader()->setVisible(false);
    setAlternatingRowColors(true);
}

IcvTableView::~IcvTableView()
{

}

void IcvTableView::setResizeMode(int logicalIndex,  QHeaderView::ResizeMode mode)
{
    horizontalHeader()->setResizeMode(logicalIndex, mode);
    return;
}

