#include <QObject>
#include <QtGui>
#include <QLineEdit>
#include <QWidget>
#include <QCompleter>
#include "icv_curve_filter.h"

IcvCurveFilterDialog::IcvCurveFilterDialog(QWidget* parent)
: QDialog(parent)
{
    setupUi(this);

    radioComandName->setCheckable(true);
    radioComandName->setChecked(true);

    QStringList wordList;
    wordList << "gettxpsd" << "getsnr" << "getnoisemargin" << "gethlog"<<"getqln"<<"getbitalloc";
    completer = new QCompleter(wordList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    lineEdit->setCompleter(completer);
    lineEdit->setFocus();
    
    lookupType = ICV_BY_COMANDNAME;
    keywords<<"getTxPsd"<<"getSnr"<<"getQln"<<"getHlog"<<"getNoiseMargin"<<"DS"<<"US";

    connect(radioCompleteComand, SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 
    connect(radioComandName,     SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 
    connect(radioLineId,         SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 
    connect(radioDirection,      SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(this, SIGNAL(previewSignal(qint16, QString)), parent, SLOT(filterCurvePreview(qint16, QString)));
    connect(this, SIGNAL(recoverPreviewSignal()), parent, SLOT(recoverCurveVisible()));


}


IcvCurveFilterDialog::~IcvCurveFilterDialog()
{

}


void IcvCurveFilterDialog::prepareCommitAction()
{
    if(sender() == radioCompleteComand)
        lookupType = ICV_BY_COMPLETECOMAND;
    else if(sender() == radioComandName)
        lookupType = ICV_BY_COMANDNAME;
    else if(sender() == radioLineId)
        lookupType = ICV_BY_LINEID;
    else if(sender() == radioDirection)
        lookupType = ICV_BY_DIRECTION;

    /*validation constraints*/
   if(radioLineId->isChecked())
    {
        QRegExp constraint("[0-9]|[1-9]([0-9]{,2})");   
        lineEdit->setValidator(new QRegExpValidator(constraint, lineEdit)); 
    }
   else
       lineEdit->setValidator(NULL);

   /* keywords completion */
   QStringList wordList;
   if (radioComandName->isChecked())
   {
       wordList << "gettxpsd" << "getsnr" << "getnoisemargin" << "gethlog"<<"getqln"<<"getbitalloc";
   }
   else if(radioDirection->isChecked())
   {
       wordList << "us" << "ds" << "0" << "1";
   }
   else if(radioCompleteComand->isChecked())
   {
       wordList << "gettxpsd" << "getsnr" << "getnoisemargin" << "gethlog"<<"getqln"<<"getbitalloc";
   }
  
   completer = new QCompleter(wordList);
   completer->setCaseSensitivity(Qt::CaseInsensitive);
   completer->setCompletionMode(QCompleter::PopupCompletion);
   lineEdit->setCompleter(completer);

   /*preview action */
   if(previewCheckBox->checkState() == Qt::Checked )
   {
       emit previewSignal(lookupType, keyword);
       return;
   }

    return;
}


qint16 IcvCurveFilterDialog::getLookupType()
{
    return lookupType;
}


QString IcvCurveFilterDialog::getKeyword()
{
    return keyword;
}


void IcvCurveFilterDialog::accept()
{
    QString userInput = lineEdit->text();
    if (radioComandName->isChecked())
    {
        QRegExp  expr;
        expr.setPattern("psd|snr|margin|qln|hlog|bit");
        expr.setCaseSensitivity(Qt::CaseInsensitive);
        if(!userInput.contains(expr))
        {
            QMessageBox::warning(this,tr("Warning"),tr("coomand name invalid!"));
            lineEdit->setFocus();

            return;
        }
    }
    else if(radioDirection->isChecked())
    {
        if(!userInput.contains(QRegExp("us|ds|0|1",Qt::CaseInsensitive)))
        {
            QMessageBox::warning(this,tr("Warning"),tr("direction invalid!"));
            lineEdit->setFocus();

            return;
        }
    }
    else if(radioCompleteComand->isChecked())
    {
        QRegExp  expr;
        expr.setPattern("(gettxpsd|getsnr|getnoisemargin|gethlog|getqln|getbitalloc)[ ]+[0-9]+[ ]+[0|1]");
        expr.setCaseSensitivity(Qt::CaseInsensitive);
        if(!userInput.contains(expr))
        {
            QMessageBox::warning(this,tr("Warning"),tr("coomand name invalid!"));
            lineEdit->setFocus();

            return;
        }
    }
    else if(!radioLineId->isChecked())
    {
        if(!userInput.contains(QRegExp("[0-9]|([1-9]([0-9]{,2})",Qt::CaseInsensitive)))
        {
            QMessageBox::warning(this,tr("Warning"),tr("direction invalid!"));
            lineEdit->setFocus();

            return;   
        }
    }

    if(!radioCompleteComand->isChecked())
    {
        for(qint16 cnt = 0; cnt < keywords.count(); cnt++)
        {
            if(lineEdit->text().contains(keywords.at(cnt), Qt::CaseInsensitive))
            {
                keyword = keywords.at(cnt);
                if(keyword == "1")
                    keyword = "DS";

                if(keyword == "0")
                    keyword = "US";
            }
        }
    }
    else
    {
        keyword = lineEdit->text();
    }


    if(previewCheckBox->checkState() == Qt::Checked )
    {
        emit previewSignal(lookupType, lineEdit->text());
        return;
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


