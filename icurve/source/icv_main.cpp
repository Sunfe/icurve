#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QClipboard>
#include <QDir>
#include <QMessageBox>
#include "icv_icurve.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    IcvICurve mainWin;
    QDesktopWidget *pDesk = QApplication::desktop();
   
    mainWin.resize(1200,800);
    mainWin.move((pDesk->width() - mainWin.width())/2, (pDesk->height() - mainWin.height())/2);
    mainWin.show();   
    return application.exec();
}

