#ifndef ICV_CURVE_FILTER_H
#define ICV_CURVE_FILTER_H

#include <QDialog>
#include <QString>
#include "ui_icv_curve_filter.h"

#define ICV_BY_COMPLETECOMAND 1
#define ICV_BY_COMANDNAME     2
#define ICV_BY_LINEID         3
#define ICV_BY_DIRECTION      4


class IcvCurveFilterDialog : public QDialog, public Ui::IcvCurveFilterDialog
{
    Q_OBJECT
public:
    IcvCurveFilterDialog(QWidget* parent=0);
    ~IcvCurveFilterDialog();

    qint16 getFilterType();
    void accept();
    void reject();

private slots:
    void setFilterType();


/*data*/
private:
    qint16 filterType;

};

#endif
