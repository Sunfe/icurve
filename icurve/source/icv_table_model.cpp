#include "icv_table_model.h"

IcvTableModel::IcvTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

IcvTableModel::~IcvTableModel()
{

}

bool IcvTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    return true;
}

QVariant IcvTableModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        return QVariant(QString(tr("String%1")).arg((index.column() + 1) * 1000 + index.row() + 1));
    case Qt::ForegroundRole:
#if 0
        switch(index.column() % 3)
        {
        case 0:
            return QVariant(QColor(Qt::red));
        case 1:
            return QVariant(QColor(Qt::green));
        case 2:
            return QVariant(QColor(Qt::blue));
        default://only to disable warning
            return QVariant(QColor(Qt::white));
        }
#endif
        break;
    default:
        return QVariant();
    }
}

int IcvTableModel::rowCount(const QModelIndex &parent) const
{

    return 10;
}

int IcvTableModel::columnCount(const QModelIndex &parent) const
{

    return 10;
}
