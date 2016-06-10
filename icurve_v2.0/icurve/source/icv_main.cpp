#include "icv_icurve.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    IcvICurve mainWin;
    mainWin.resize(800,600);
    mainWin.show();

    //application.setWindowIcon(QIcon("../images/cash-add.png"));
    return application.exec();
}
