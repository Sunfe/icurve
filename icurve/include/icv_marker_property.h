#ifndef ICV_MARKER_PROPERTY_H
#define ICV_MARKER_PROPERTY_H
#include <QDialog>
#include <QString>
#include <QBrush>
#include <QPen>
#include "ui_icv_marker_property.h"

class IcvMarkerPropertyDialog : public QDialog, public Ui::IcvMarkerProperty
{
    Q_OBJECT
public:
    IcvMarkerPropertyDialog(QWidget* parent=0);
    ~IcvMarkerPropertyDialog();

    void accept();
    void reject();
    QBrush getMarkerBrush();
    QPen getMarkerPen();

    QIcon createColorToolButtonIcon(const QString imageFile, QColor color);
private slots:
    void setMarkerBush();
    void setMarkerPen();

private:
    QBrush markerBrush;
    QPen   markerPen;

};

#endif
