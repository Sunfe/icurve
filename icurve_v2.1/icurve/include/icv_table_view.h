#ifndef ICV_TABLE_VIEW_H
#define ICV_TABLE_VIEW_H

#include <QTableView>
#include <QHeaderView>

class IcvTableView : public QTableView
{
    Q_OBJECT

public:
    IcvTableView(QWidget *parent = 0);
    ~IcvTableView();
    void setResizeMode(int logicalIndex,  QHeaderView::ResizeMode mode);

private:
    
};

#endif // ICV_TABLE_VIEW_H
