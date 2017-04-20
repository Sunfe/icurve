#ifndef ICV_REGEXP_H
#define ICV_REGEXP_H

#include <QDialog>
#include "ui_icv_regexp.h"
#include "icv_table_widget.h"

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
    IcvTableWidget *tableWidgetTitle;
    IcvTableWidget *tableWidgetData;
    IcvTableWidget *tableWidgetSpec;
};

#endif // ICV_REGEXP_H
