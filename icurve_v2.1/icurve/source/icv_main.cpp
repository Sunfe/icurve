#include "icv_icurve.h"
#include <QtGui/QApplication>
#include <QClipboard>
#include <QDir>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
#if 0
    QMessageBox::warning(NULL,"", QDir::currentPath());
#endif
    IcvICurve mainWin;
    mainWin.resize(800,600);
    mainWin.show();   
    //QApplication::addLibraryPath("./plugins");

    return application.exec();
}

