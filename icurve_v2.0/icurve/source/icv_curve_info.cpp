#include <QObject>
#include <QtGui>
#include "icv_curve_info.h"

IcvCurveInfoDialog::IcvCurveInfoDialog(QList<IcvPlotCurve*> curveList, QWidget* parent, Qt::WindowFlags flag):
QDialog(parent,flag)
{
    setupUi(this);
    setWindowTitle("show curve information");

    if(curveList.isEmpty())
        return ;

    curves = curveList;
    QStringList curveTitile;
    for(qint16 cnt = 0; cnt < curves.count(); cnt++)
    {
        QString title = curves.at(cnt)->getCommand().getCommandTitle();
        curveTitile.append(title);     
    }
    comboBoxCurveTitle->addItems(curveTitile);
    comboBoxCurveTitle->setParent(this);
    connect(comboBoxCurveTitle, SIGNAL(activated(int)), this, SLOT(setCurveFileInfo(int)));

    plainTextEditFilePos->setReadOnly(true);
    QString posInfo  = "at line " +
                        QString::number(curves.at(0)->getCommand().getDataPosInFile()) + 
                        " of file \"" + curves.at(0)->getCommand().getFileName() +"\"";
    plainTextEditFilePos->setPlainText(posInfo);

    plainEditFileBriefInfo->setReadOnly(true);
    plainEditFileBriefInfo->setPlainText(curves.at(0)->getCommand().getBriefInfo());

}


IcvCurveInfoDialog::~IcvCurveInfoDialog(void)
{

}


void IcvCurveInfoDialog::setCurveFileInfo(int index)
{
    if(index > curves.count())
        return;

    IcvPlotCurve *curve   = curves.at(index);
    QString      posInfo  = "at line " + \
                             QString::number(curve->getCommand().getDataPosInFile()) + 
                             " of file \"" + curve->getCommand().getFileName() +"\"";
    plainTextEditFilePos->setPlainText(posInfo);
    plainEditFileBriefInfo->setPlainText(curve->getCommand().getBriefInfo());

    return;
}


