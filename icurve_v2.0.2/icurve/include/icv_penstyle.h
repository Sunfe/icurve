
#include <QObject>
#include <QPainter>
#include <QAbstractItemDelegate>
#include <QStyleOptionViewItem>
#include <QModelIndex>


class IcvPenStyleDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit IcvPenStyleDelegate(QObject *parent = 0);

    void paint(QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
        const QModelIndex &index) const;

signals:

public slots:

};
