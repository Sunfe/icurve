#include "icv_penstyle.h"

IcvPenStyleDelegate::IcvPenStyleDelegate(QObject *parent):
QAbstractItemDelegate(parent)
{

}

void IcvPenStyleDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    QString test = index.data(Qt::DisplayRole).toString();
    Qt::PenStyle penStyle = (Qt::PenStyle)index.data(Qt::UserRole).toInt();
    QRect r = option.rect;

    if(option.state & QStyle::State_Selected)
    {
        painter->save();
        painter->setBrush(option.palette.highlight());
        painter->setPen(Qt::NoPen);
        painter->drawRect(option.rect);
        painter->setPen(QPen(option.palette.highlightedText(),2,penStyle));
    }
    else
    {
        painter->setPen(penStyle);
    }

    painter->drawLine(0,r.y()+r.height()/2,r.right(),r.y()+r.height()/2);

    if(option.state & QStyle::State_Selected)
        painter->restore();

    return;
}


QSize IcvPenStyleDelegate::sizeHint(const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    return QSize(100,30);
}

