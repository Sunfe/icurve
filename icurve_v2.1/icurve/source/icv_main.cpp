#include <QtGui/QApplication>
#include <QClipboard>
#include <QDir>
#include <QMessageBox>
#include "icv_icurve.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    IcvICurve mainWin;
    mainWin.resize(800,600);
    mainWin.show();   
    return application.exec();
}

