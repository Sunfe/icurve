#include <QtGui>
#include "icv_curve_statistics.h"


IcvCurveStatistics::IcvCurveStatistics(QAbstractItemModel * model,QWidget * parent = 0)
    : QTableView(parent)
{
    setModel(model);
    statTableView = new QTableView(this);

    connect(horizontalHeader(),SIGNAL(sectionResized(int,int,int)), this,
        SLOT(updateSectionWidth(int,int,int)));
    connect(verticalHeader(),SIGNAL(sectionResized(int,int,int)), this,
        SLOT(updateSectionHeight(int,int,int)));

    connect(verticalScrollBar(), SIGNAL(valueChanged(int)),
        verticalScrollBar(), SLOT(setValue(int)));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)),
        verticalScrollBar(), SLOT(setValue(int)));
}

IcvCurveStatistics::~IcvCurveStatistics()
{
    delete statTableView;
}

void IcvCurveStatistics::init()
{
    setModel(model());
    setFocusPolicy(Qt::NoFocus);
    horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateFrozenTableGeometry();
    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    return;
}

void IcvCurveStatistics::updateSectionWidth(int logicalIndex, int, int newSize)
{
    if(logicalIndex==0){
        setColumnWidth(0,newSize);
        updateFrozenTableGeometry();
    }
    return;
}

void IcvCurveStatistics::updateSectionHeight(int logicalIndex, int, int newSize)
{
    setRowHeight(logicalIndex, newSize);
    return;
}

void IcvCurveStatistics::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);
    updateFrozenTableGeometry();
    return;
}

QModelIndex IcvCurveStatistics::moveCursor(CursorAction cursorAction,
                                           Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);
    if(cursorAction == MoveLeft && current.column()>0
        && visualRect(current).topLeft().x() < columnWidth(0) ){

            const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                - columnWidth(0);
            horizontalScrollBar()->setValue(newValue);
    }
    return current;
}

void IcvCurveStatistics::scrollTo (const QModelIndex & index, ScrollHint hint)
{
    if(index.column()>0)
        QTableView::scrollTo(index, hint);
    return;
}

void IcvCurveStatistics::updateFrozenTableGeometry()
{
    setGeometry(verticalHeader()->width()+frameWidth(), frameWidth(), columnWidth(0),
                viewport()->height()+horizontalHeader()->height());
    return;
}




