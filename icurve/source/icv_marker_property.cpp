#include <QObject>
#include <QtGui>
#include <QLineEdit>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include "icv_marker_property.h"

IcvMarkerPropertyDialog::IcvMarkerPropertyDialog(QWidget* parent)
: QDialog(parent)
{
    setupUi(this);
    sizeLineEdit->setFocus();
    /*marker bush*/
    btnMarkerBrush->setIcon(createColorToolButtonIcon(tr("images/floodfill.png"),
                            markerBrush.color()));
    connect(btnMarkerBrush,SIGNAL(clicked()), this, SLOT(setMarkerBush()));

    /*marker pen*/
    btnMarkerPen->setIcon(createColorToolButtonIcon(tr("images/linecolor.png"),
                          markerPen.color()));
    connect(btnMarkerPen,SIGNAL(clicked()), this, SLOT(setMarkerPen()));
}

IcvMarkerPropertyDialog::~IcvMarkerPropertyDialog()
{

}

void IcvMarkerPropertyDialog::setMarkerBush()
{
    QColor colorUsing = markerBrush.color();
    QColor      color = QColorDialog::getColor(colorUsing,this,tr("Select color"));
    markerBrush = QBrush(color);
    btnMarkerBrush->setIcon(createColorToolButtonIcon(tr("images/floodfill.png"),color));
    return;
}

void IcvMarkerPropertyDialog::setMarkerPen()
{
    QColor colorUsing = markerPen.color();
    QColor      color = QColorDialog::getColor(colorUsing,this,tr("Select color"));
    markerPen = QPen(color);
    btnMarkerPen->setIcon(createColorToolButtonIcon(tr("images/linecolor.png"),color));
    return ;
}

QIcon IcvMarkerPropertyDialog::createColorToolButtonIcon(const QString imageFile, QColor color)
{
    QPixmap pixmap(50,80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QPixmap image(imageFile);
    QRect target(0,0,50,60);
    QRect source(0,0,42,42);
    painter.fillRect(QRect(0,60,50,80),color);
    painter.drawPixmap(target,image, source);
    return QIcon(pixmap);
}

QBrush IcvMarkerPropertyDialog::getMarkerBrush()
{
    return markerBrush;
}

QPen IcvMarkerPropertyDialog::getMarkerPen()
{
    return markerPen;
}

void IcvMarkerPropertyDialog::accept()
{
    if(sizeLineEdit->text() == "")
    {
        QMessageBox::warning(this,tr("Warning"),tr("No input for size."));
        sizeLineEdit->setFocus();
        return ;
    }
    if(sizeLineEdit->text() != "")
    {
        bool ok = false;
        qint16 size = (sizeLineEdit->text().toInt(&ok));
        if(!ok)
        {
            QMessageBox::warning(this,tr("Warning"),tr("Need a integer number."));
            sizeLineEdit->setFocus();
            return ;
        }
    }
    return QDialog::accept ();
}

void IcvMarkerPropertyDialog::reject()
{
  return QDialog::reject ();
}


