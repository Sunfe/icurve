#ifndef ICV_CURVE_INFO_H
#define ICV_CURVE_INFO_H

#include <Qt>
#include <QDialog>
#include <QWidget>
#include <QList>
#include "ui_icv_curve_info.h"
#include "icv_plot_curve.h"

class IcvPlotCurve;
class IcvCurveInfoDialog: public QDialog, public Ui::IcvCurveInfo
{
    Q_OBJECT
public:
    IcvCurveInfoDialog(QList<IcvPlotCurve*> curve, QWidget* parent, Qt::WindowFlags flag );
    ~IcvCurveInfoDialog(void);

    private slots:
        void setCurveFileInfo(int index);

private:
    QList<IcvPlotCurve*> curves;

signals:
  //  void setCurveInfoSignal(QString name, QString position, QString lineInfo);


};

#endif