#include "icv_icurve.h"
#include <QtGui/QApplication>
#include <QClipboard>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    IcvICurve mainWin;
    mainWin.resize(800,600);
    mainWin.show();

    //QString dir = QApplication::applicationDirPath();  
    //application.setWindowIcon(QIcon(":/icurve/../images/iCurve.ico"));
    
    QApplication::addLibraryPath("./plugins");
    return application.exec();
}

