/********************************************************************************
** Form generated from reading UI file 'icurve.ui'
**
** Created: Fri May 13 22:33:48 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICURVE_H
#define UI_ICURVE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_icurveClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *icurveClass)
    {
        if (icurveClass->objectName().isEmpty())
            icurveClass->setObjectName(QString::fromUtf8("icurveClass"));
        icurveClass->resize(600, 400);
        actionOpen = new QAction(icurveClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(icurveClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        centralWidget = new QWidget(icurveClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        icurveClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(icurveClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        icurveClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(icurveClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        icurveClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(icurveClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        icurveClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);

        retranslateUi(icurveClass);

        QMetaObject::connectSlotsByName(icurveClass);
    } // setupUi

    void retranslateUi(QMainWindow *icurveClass)
    {
        icurveClass->setWindowTitle(QApplication::translate("icurveClass", "icurve", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("icurveClass", "open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("icurveClass", "save as", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("icurveClass", "file", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class icurveClass: public Ui_icurveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICURVE_H
