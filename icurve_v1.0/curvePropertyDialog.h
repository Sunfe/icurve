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

//#include "iCurve.h"
#include "curvePainter.h"

class iCurve;

class CurvePropertyDialog : public QDialog
{
    Q_OBJECT

    public:
        CurvePropertyDialog(QWidget * parent = 0, Qt::WindowFlags flag = 0);
        ~CurvePropertyDialog();

    public:
        iCurve* figure();
        const iCurve* figure() const;

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
        QLabel *nameLabel;
        QLabel *lineLabel;
        QLineEdit *nameText;
        QComboBox *lineTypeCombox;
        QComboBox *curveWidthCombox;
        QPushButton *btnLineColor;

        QLabel *markerLabel;
        QComboBox *markerTypeCombox;
        QComboBox *markerSizeCombox;
        QPushButton *btnMarkerBrush;
        QPushButton *btnMarkerPen;

        Qt::PenStyle curveStyle;
        int curveWidth;
        QColor curveColor;
        QwtSymbol::Style markerStyle;
        QBrush markerBrush;
        QPen markerPen;
        QSize markerSize;

};


#endif


