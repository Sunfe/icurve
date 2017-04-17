#ifndef ICV_REGEXP_H
#define ICV_REGEXP_H

#include <QDialog>
#include "ui_icv_regexp.h"

class IcvRegExp : public QDialog, public Ui::IcvRegExp
{
    Q_OBJECT

public:
    IcvRegExp(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~IcvRegExp();

private slots:
        void accept();
        void reject();
        
private:
    QTableWidget *tableWidgetTitle;
    QTableWidget *tableWidgetData;
    QTableWidget *tableWidgetSpec;
};

#endif // ICV_REGEXP_H
