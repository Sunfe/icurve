#include <QObject>
#include <QtGui>
#include <QLineEdit>
#include <QWidget>
#include "icv_curve_filter.h"

IcvCurveFilterDialog::IcvCurveFilterDialog(QWidget* parent)
: QDialog(parent)
{
    setupUi(this);
    lineEdit->setFocus();
    ByComandNameRadio->setCheckable(true);
    ByComandNameRadio->setChecked(true);

    connect(ByCompleteComandRadio, SIGNAL(clicked()), this, SLOT(setFilterType())); 
    connect(ByComandNameRadio,     SIGNAL(clicked()), this, SLOT(setFilterType())); 
    connect(ByLineIdRadio,         SIGNAL(clicked()), this, SLOT(setFilterType())); 
    connect(ByDirectionRadio,      SIGNAL(clicked()), this, SLOT(setFilterType())); 

    filterType = ICV_BY_COMANDNAME;

}


IcvCurveFilterDialog::~IcvCurveFilterDialog()
{

}


void IcvCurveFilterDialog::setFilterType()
{

    if(sender() == ByCompleteComandRadio)
        filterType = ICV_BY_COMPLETECOMAND;
    else if(sender() == ByComandNameRadio)
        filterType = ICV_BY_COMANDNAME;
    else if(sender() == ByLineIdRadio)
        filterType = ICV_BY_LINEID;
    else if(sender() == ByDirectionRadio)
        filterType = ICV_BY_DIRECTION;

    return;
}


qint16 IcvCurveFilterDialog::getFilterType()
{
    return filterType;
}


void IcvCurveFilterDialog::accept()
{
    if(!ByCompleteComandRadio->isChecked() &&
        !ByComandNameRadio->isChecked() &&
        !ByLineIdRadio->isChecked()&&
        !ByDirectionRadio->isChecked())
    {
        QMessageBox::warning(this,tr("Warning"),tr("Please select a filter type."));
        return ;
    }

    if(lineEdit->text() == "")
    {
        QMessageBox::warning(this,tr("Warning"),tr("Please input keyword."));
        return ;
    }


    return QDialog::accept ();
}


void IcvCurveFilterDialog::reject()
{
  return QDialog::reject ();
}