#ifndef ICV_TABLE_WIGET_H
#define ICV_TABLE_WIGET_H
#include <Qt>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMenu>
#include <QContextMenuEvent>

#define ICV_MAX_TBLWGT_ROW     (100)
#define ICV_MAX_TBLWGT_COL     (100)

class IcvTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    IcvTableWidget(QWidget *parent);
    IcvTableWidget(int rows, int columns, QWidget *parent = 0);
    ~IcvTableWidget();
    void setTableSize(int rows, int columns);
    void setHeaderVisible(bool horVisible, bool verVisible);
    void setResizeMode(int logicalIndex,  QHeaderView::ResizeMode mode);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void appendCellText(int row, int column);
    void copyToExcel();

private:
    QMenu   *popMenu;
    QAction *copyAct;
    QString cellText[ICV_MAX_TBLWGT_ROW][ICV_MAX_TBLWGT_COL];
    QList<int>  selectRow;
    QList<int>  selectCol;
};



#endif // ICV_TABLE_WIGET_H
