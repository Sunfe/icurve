#include <QObject>
#include <QtGui>
#include <QLineEdit>
#include <QWidget>
#include <QCompleter>
#include <QSize>
#include "icv_curve_filter.h"

#define ICV_HEIGHT_MORE_SELECT_AREA    (30)


IcvCurveFilterDialog::IcvCurveFilterDialog(QWidget* parent)
: QDialog(parent)
{
    setupUi(this);
    resize(410, 225 - ICV_HEIGHT_MORE_SELECT_AREA);
    radioComandName->setCheckable(true);
    radioComandName->setChecked(true);
    radioPromt->setVisible(false);
    radioCompleteComand->setVisible(false);
    radioPosition->setVisible(false);
    QSize sz = groupBox->size();
    groupBox->resize(sz.width(), sz.height()-30);

    QRect rect = widget->geometry();
    QPoint pnt = rect.topLeft();
    rect.moveTopLeft(QPoint(pnt.x(), pnt.y()-30));
    widget->setGeometry(rect);

    /* default completion */
    QStringList wordList;
    wordList << "gettxpsd" << "getsnr" << "getnoisemargin" << "gethlog"<<"getqln"<<"getbitalloc"\
             << "psd" <<"snr" << "margin" << "hlog" << "bitalloc" << "rmcbitalloc"\
             << "bitload"<< "qln"<< "snr"<<"gainalloc"<<"hlog"<<"linimg"<<"linreal"\
             << "bcm" <<"rfc"<< "api" <<"fast";
    completer = new QCompleter(wordList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    lineEdit->setCompleter(completer);
    lineEdit->setFocus();

    lookupType = ICV_BY_COMANDNAME;
    /* legally accept command name*/
    keywords << "getTxPsd" << "getSnr" << "getQln" << "getHlog" << "getNoiseMargin" << "getBitAlloc"\
        << "DS" << "US"<<"api"<<"rfc"<<"bcm"<<"fast";
    /* default actions */

    connect(radioComandName,     SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 
    connect(radioLineId,         SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 
    connect(radioDirection,      SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 
    connect(radioCompleteComand, SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 
    connect(radioPromt,          SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 
    connect(radioPosition,       SIGNAL(clicked()), this, SLOT(prepareCommitAction())); 

    connect(this, SIGNAL(previewSignal(qint16, QString, qint16)), parent, SLOT(filterCurvePreview(qint16, QString, qint16)));
    connect(this, SIGNAL(recoverPreviewSignal()), parent, SLOT(recoverCurveVisible()));
    connect(this, SIGNAL(warningSignal(QString)), this, SLOT(displayWarning(QString)));
    connect(moreButton, SIGNAL(toggled(bool)), this, SLOT(toggleMoreSelect(bool)));
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
    else if(sender() == radioPromt)
        lookupType = ICV_BY_PROMT;
    else if(sender() == radioPosition)
        lookupType = ICV_BY_POS;    
    /*validation constraints*/
    if(radioLineId->isChecked() || radioPosition->isChecked())
    {
        QRegExp constraint("^[0-9]+|^([0-9]+,){1,}[0-9]?|^[0-9]+:[0-9]+");   
        lineEdit->setValidator(new QRegExpValidator(constraint, lineEdit)); 
    }
    else
        lineEdit->setValidator(NULL);
    /* keywords completion */
    QStringList wordList;
    if (radioComandName->isChecked())
    {
        wordList << "gettxpsd" << "getsnr" << "getnoisemargin" << "gethlog"<<"getqln"<<"getbitalloc"<<"getrmcbitalloc"
                 << "bitload"<< "qln"<< "snr"<<"gainalloc"<<"hlog"<<"linimg"<<"linreal";
    }
    else if(radioDirection->isChecked())
    {
        wordList << "us" << "ds" << "0" << "1";
    }
    else if(radioCompleteComand->isChecked())
    {
        wordList << "gettxpsd" << "getsnr" << "getnoisemargin" << "gethlog"<<"getqln"<<"getbitalloc"<<"getrmcbitalloc";
    }
    else if(radioPromt->isChecked())
    {
        wordList << "rfc" << "bcm" << "api" << "fast";
    }

    completer = new QCompleter(wordList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    lineEdit->setCompleter(completer);
    /*preview action */
    if(previewCheckBox->checkState() == Qt::Checked )
    {
        emit previewSignal(lookupType, keyword, getInAllCheckState());
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

Qt::CheckState IcvCurveFilterDialog::getInAllCheckState()
{
    return inAllCheckBox->checkState();
}

void IcvCurveFilterDialog::accept()
{
    QString userInput = lineEdit->text();
    if (radioComandName->isChecked())
    {
        QRegExp  expr;
        expr.setPattern("psd|snr|margin|qln|hlog|bit|linimg|linreal");
        expr.setCaseSensitivity(Qt::CaseInsensitive);
        if(!userInput.contains(expr))
        {
            emit warningSignal("command name invalid!");
            lineEdit->setFocus();
            return;
        }
    }
    else if(radioDirection->isChecked())
    {
        if(!userInput.contains(QRegExp("us|ds|0|1",Qt::CaseInsensitive)))
        {
            emit warningSignal("direction invalid!");
            lineEdit->setFocus();
            return;
        }
    }
    else if(radioCompleteComand->isChecked())
    {
        QRegExp  expr;
        expr.setPattern("(gettxpsd|getsnr|getnoisemargin|gethlog|getqln|getbitalloc|getrmcbitalloc)[ ]+[0-9]+[ ]+[0|1]");
        expr.setCaseSensitivity(Qt::CaseInsensitive);
        if(!userInput.contains(expr))
        {
            emit warningSignal("complete command name invalid!");
            lineEdit->setFocus();
            return;
        }
    }
    else if(radioLineId->isChecked())
    {
        if(!userInput.contains(QRegExp("[0-9]|([1-9][0-9]+)",Qt::CaseInsensitive)))
        {
            emit warningSignal("lineid invalid!");
            lineEdit->setFocus();
            return;   
        }
    }
    else if(radioPromt->isChecked())
    {
        if(!userInput.contains(QRegExp("rfc|bcm|api|fast",Qt::CaseInsensitive)))
        {
            emit warningSignal("promt invalid!");
            lineEdit->setFocus();
            return;
        }
    }

    keyword = lineEdit->text();
    if(radioDirection->isChecked())
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
    else if(radioComandName->isChecked())
    {
        QRegExp expr("psd|gettxpsd|snr|getsnr|margin|getnoisemargin|qln|getqln|hlog|gethlog|bit|getbitalloc|getrmcbitalloc|linimg|linreal");
        if(lineEdit->text().contains(expr))
        {
            QString word = expr.cap(0);
            QStringList keywordList = keywords.filter(word, Qt::CaseInsensitive);
            if(keywordList.count() == 0)
                return;

            keyword = keywordList[0];
            if(lineEdit->text().length() > word.length())
            {
                QMessageBox msgBox(this);
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setText("A fuzzy matching: " + word + " is detected,you want continue?");
                qint16 retcode = msgBox.exec();
                if(QDialog::Rejected == retcode)
                    return;
            }
        }
    }
    else if(radioPromt->isChecked())
    {
        QRegExp expr("rfc|api|bcm|fast");
        if(lineEdit->text().contains(expr))
        {
            QString word = expr.cap(0);
            QStringList keywordList = keywords.filter(word, Qt::CaseInsensitive);
            if(keywordList.count() == 0)
                return;

            keyword = keywordList[0];
            if(lineEdit->text().length() > word.length())
            {
                QMessageBox msgBox(this);
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setText("A fuzzy matching: " + word + " is detected,you want continue?");
                qint16 retcode = msgBox.exec();
                if(QDialog::Rejected == retcode)
                    return;
            }
        }
    }

    if(previewCheckBox->checkState() == Qt::Checked )
    {
        emit previewSignal(lookupType, lineEdit->text(), getInAllCheckState());
        return ;
    }
    else
    {
        return QDialog::accept();
    }
}

void IcvCurveFilterDialog::reject()
{
    if(previewCheckBox->checkState() == Qt::Checked )
    {
        emit recoverPreviewSignal();
        return;
    }
    return QDialog::reject ();
}

void IcvCurveFilterDialog::displayWarning(QString info)
{
    QMessageBox::warning(this,tr("Warning"), info, QMessageBox::Close);
    return QDialog::reject () ;
}

void IcvCurveFilterDialog::showMoreSelect()
{
    radioPromt->setVisible(true);
    radioCompleteComand->setVisible(true);
    radioPosition->setVisible(true);

    QSize sz = groupBox->size();
    groupBox->resize(sz.width(), sz.height() + ICV_HEIGHT_MORE_SELECT_AREA);

    QRect rectWgt = widget->geometry();
    QPoint pnt = rectWgt.topLeft(); 
    rectWgt.moveTopLeft(QPoint(pnt.x(), pnt.y() + ICV_HEIGHT_MORE_SELECT_AREA));
    widget->setGeometry(rectWgt);

    QRect rectMe = geometry();
    resize(rectMe.width(), rectMe.height() + ICV_HEIGHT_MORE_SELECT_AREA);
    return;
}

void IcvCurveFilterDialog::hideMoreSelect()
{
    QRect rect = widget->geometry();
    QPoint pnt = rect.topLeft(); 

    radioPromt->setVisible(false);
    radioCompleteComand->setVisible(false);
    radioPosition->setVisible(false);

    QSize sz = groupBox->size();
    groupBox->resize(sz.width(), sz.height() - ICV_HEIGHT_MORE_SELECT_AREA);
    rect.moveTopLeft(QPoint(pnt.x(), pnt.y() - ICV_HEIGHT_MORE_SELECT_AREA));
    widget->setGeometry(rect);

    QRect rectMe = geometry();
    resize(rectMe.width(), rectMe.height() - ICV_HEIGHT_MORE_SELECT_AREA);
    return;
}

void IcvCurveFilterDialog::toggleMoreSelect(bool needMore)
{
    return needMore? showMoreSelect(): hideMoreSelect();
}
