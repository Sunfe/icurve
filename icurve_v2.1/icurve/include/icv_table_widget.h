#ifndef ICV_TABLE_WIGET_H
#define ICV_TABLE_WIGET_H
#include <Qt>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMenu>
#include <QContextMenuEvent>

class IcvTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    IcvTableWidget(QWidget *parent);
    ~IcvTableWidget();
    void setTableSize(int rows, int columns);
    void setHeaderVisible(bool horVisible, bool verVisible);
    void setResizeMode(int logicalIndex,  QHeaderView::ResizeMode mode);
    void contextMenuEvent(QContextMenuEvent *event);
private:
    QMenu *popMenu;
};

#endif // ICV_TABLE_WIGET_H
