#ifndef _CURVE_PROPERTY_DIALOG_H
#define _CURVE_PROPERTY_DIALOG_H

#include <Qt>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QComboBox>
#include <QString>
#include <QMessageBox>
#include <QPixmap>
#include <QPen>
#include <QPainter>
#include <QIcon>
#include <QVariant>
#include <QSize>

#include "qwt_plot_curve.h"
#include "qwt_plot.h"
#include "qwt_symbol.h"

#include "icv_icurve.h"

class IcvICurve;

class IcvCurvePropertyDialog : public QDialog
{
    Q_OBJECT

public:
    IcvCurvePropertyDialog(IcvPlotCurve *crv, QWidget *parent, Qt::WindowFlags flag);
    ~IcvCurvePropertyDialog();

protected:
    bool eventFilter (  QObject * obj, QEvent * event );

    private slots:
        void accept();
        void reject();
        void setCurveStyle(int indexSel);
        void setCurveWidth(int indexSel);
        void setCurveColor();

        void setMarkerStyle(int indexSel);
        void setMarkerBush();
        void setMarkerPen();
        void setMarkerSize(int indexSel);

private:
    QIcon createColorToolButtonIcon(const QString imageFile, QColor color);
    QwtPlotCurve* getCurve();
    const QwtSymbol* getSymbol();

    /*data member*/
private:
    IcvPlotCurve *curve;

    QLabel          *nameLabel;
    QLabel          *lineLabel;
    QLineEdit       *nameText;
    QComboBox       *lineTypeCombox;
    QComboBox       *curveWidthCombox;
    QPushButton     *btnLineColor;

    QLabel          *markerLabel;
    QComboBox       *markerTypeCombox;
    QComboBox       *markerSizeCombox;
    QPushButton     *btnMarkerBrush;
    QPushButton     *btnMarkerPen;

    QwtText          curveTitile;
    Qt::PenStyle     curveStyle;
    qint16           curveWidth;
    QColor           curveColor;
    QwtSymbol::Style markerStyle;
    QBrush           markerBrush;
    QPen             markerPen;
    QSize            markerSize;

};


#endif


