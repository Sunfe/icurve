#ifndef ICV_TABLE_MODEL_H
#define ICV_TABLE_MODEL_H

#include <QAbstractTableModel>

class IcvTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    IcvTableModel(QObject *parent = 0);
    ~IcvTableModel();

    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    int iRow;
    int iCol;
};

#endif // ICV_TABLE_MODEL_H
