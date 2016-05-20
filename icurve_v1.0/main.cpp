#include "icurve.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    iCurve w;
    w.resize(600,500);
    w.show();
    return a.exec();
}
