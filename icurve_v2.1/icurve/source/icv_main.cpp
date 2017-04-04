#include <QtGui/QApplication>
#include <QClipboard>
#include <QDir>
#include <QMessageBox>
#include "icv_icurve.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    IcvICurve mainWin;
    mainWin.resize(1200,800);
    mainWin.show();   
    return application.exec();
}

