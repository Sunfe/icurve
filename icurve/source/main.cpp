#include "icurve.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	icurve mainWin;
	mainWin.resize(600,500);
	mainWin.show();
	return a.exec();
}
