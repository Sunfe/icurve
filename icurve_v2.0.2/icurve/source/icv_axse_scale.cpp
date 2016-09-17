#include <QMessageBox>
#include <QDoubleValidator>
#include "icv_axse_scale.h"


#define ICV_MIN_LIMIT_SCALE_X  (0.0)
#define ICV_MAX_LIMIT_SCALE_X  (20000.0)
#define ICV_MIN_LIMIT_SCALE_Y  (-200.0)
#define ICV_MAX_LIMIT_SCALE_Y  (200.0)


IcvAxseSCaleDialog::IcvAxseSCaleDialog(QWidget* parent)
: QDialog(parent)
{
    if (NULL == parent)
        return ;

    setupUi(this);
    lineEditMinX->setFocus();

    /* only number is allowed to input */
    class QDoubleValidator *validatorX = new QDoubleValidator(\
                                             ICV_MIN_LIMIT_SCALE_X,
                                             ICV_MAX_LIMIT_SCALE_X,1,this);
    class QDoubleValidator *validatorY = new QDoubleValidator(\
                                             ICV_MIN_LIMIT_SCALE_Y,
                                             ICV_MAX_LIMIT_SCALE_Y,1,this);

    lineEditMinX->setValidator(validatorX);
    lineEditMaxX->setValidator(validatorX);
    lineEditMinY->setValidator(validatorY);
    lineEditMaxY->setValidator(validatorY);

    QWidget::setTabOrder(lineEditMinX, lineEditMaxX);
    QWidget::setTabOrder(lineEditMaxX, lineEditMinY);
    QWidget::setTabOrder(lineEditMinY, lineEditMaxY);
    QWidget::setTabOrder(lineEditMinY, lineEditMaxY);
    QWidget::setTabOrder(lineEditMaxY, buttonBox);

}


IcvAxseSCaleDialog::~IcvAxseSCaleDialog(void)
{

}


void IcvAxseSCaleDialog::accept()
{
    bool ok = false;

	if(lineEditMinX->text().isEmpty() || lineEditMaxX->text().isEmpty() ||
	   lineEditMinY->text().isEmpty() || lineEditMaxY->text().isEmpty())
	{
		QMessageBox::warning(this,tr("Warning"),\
			tr("Empty input is not allowed."));
		lineEditMinX->setFocus();
		return;
	}

    double minX = lineEditMinX->text().toDouble(&ok);
    double maxX  = lineEditMaxX->text().toDouble(&ok);

    double minY  = lineEditMinY->text().toDouble(&ok);
    double maxY  = lineEditMaxY->text().toDouble(&ok);

    if(minX >= maxX)
    {
        QMessageBox::warning(this,tr("Warning"),\
            tr("min X should not be greater than max X"));
        lineEditMinX->setFocus();
        return;
    }

    if(minY >= maxY)
    {
        QMessageBox::warning(this,tr("Warning"),\
            tr("min Y should not be greater than max Y"));
        lineEditMinX->setFocus();
        return;
    }

    return QDialog::accept();
}


void IcvAxseSCaleDialog::reject()
{
    return QDialog::reject();
}

