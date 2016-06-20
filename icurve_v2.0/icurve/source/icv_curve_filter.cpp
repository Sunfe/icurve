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
    connect(this, SIGNAL(previewSignal(qint16, QString)), parent, SLOT(filterCurvePreview(qint16, QString)));
    connect(this, SIGNAL(recoverPreviewSignal()), parent, SLOT(recoverCurveVisible()));
    
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

    /*validation constraints*/
   if(ByLineIdRadio->isChecked())
    {
        QRegExp constraint("[0-9]|[1-9]([0-9]{,2})");   
        lineEdit->setValidator(new QRegExpValidator(constraint, lineEdit)); 
    }

    return;
}


qint16 IcvCurveFilterDialog::getFilterType()
{
    return filterType;
}


void IcvCurveFilterDialog::accept()
{
    QString keywords = lineEdit->text();
    if (ByComandNameRadio->isChecked())
    {
        QRegExp  expr;
        expr.setPattern("psd|snr|margin|qln|hlog|bit");
        expr.setCaseSensitivity(Qt::CaseInsensitive);
        if(!keywords.contains(expr))
            QMessageBox::warning(this,tr("Warning"),tr("coomand name invalid!"));
        lineEdit->setFocus();

        return ;
    }
    else if(ByDirectionRadio->isChecked())
    {
        if(!keywords.contains(QRegExp("us|ds|0|1",Qt::CaseInsensitive)))
            QMessageBox::warning(this,tr("Warning"),tr("direction invalid!"));
        lineEdit->setFocus();
        
        return;
    }
    else if(ByCompleteComandRadio->isChecked())
    {
        QRegExp  expr;
        expr.setPattern("(gettxpsd|getsnr|getnoisemargin|gethlog|getqln|getbitalloc)[ ]+[0-9]+[ ]+[0|1]");
        expr.setCaseSensitivity(Qt::CaseInsensitive);
        if(!keywords.contains(expr))
            QMessageBox::warning(this,tr("Warning"),tr("coomand name invalid!"));
        lineEdit->setFocus();

        return;
    }
    else if(!ByLineIdRadio->isChecked())
    {
        if(!keywords.contains(QRegExp("[0-9]|([1-9]([0-9]{,2})",Qt::CaseInsensitive)))
            QMessageBox::warning(this,tr("Warning"),tr("direction invalid!"));
        lineEdit->setFocus();

        return;   
    }

    if(previewCheckBox->checkState() == Qt::Checked )
    {
        emit previewSignal(filterType, lineEdit->text());
        return ;
    }

    return QDialog::accept();
}


void IcvCurveFilterDialog::reject()
{
    if(previewCheckBox->checkState() == Qt::Checked )
    {
        emit recoverPreviewSignal();
    }

  return QDialog::reject ();
}