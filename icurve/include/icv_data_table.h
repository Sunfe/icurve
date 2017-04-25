#ifndef ICV_DATA_TABLE_H
#define ICV_DATA_TABLE_H

#include <QWidget>
#include <QDialog>
#include "ui_icv_data_table.h"

class IcvDataTable : public QDialog
{
    Q_OBJECT

public:
    IcvDataTable(QWidget *parent = 0);
    ~IcvDataTable();

private:
    Ui::IcvDataTable ui;
};

#endif // ICV_DATA_TABLE_H
