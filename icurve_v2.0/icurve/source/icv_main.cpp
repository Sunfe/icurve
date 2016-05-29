#include "icv_icurve.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IcvICurve mainWin;
    mainWin.resize(800,600);
    mainWin.show();
    return a.exec();
}
