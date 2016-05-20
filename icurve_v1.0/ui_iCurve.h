/********************************************************************************
** Form generated from reading UI file 'icurve.ui'
**
** Created: Mon May 5 11:05:46 2014
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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_iCurveClass
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionAbout;
    QAction *actionTitle;
    QAction *actionSaveAs;
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuTitles;

    void setupUi(QMainWindow *iCurveClass)
    {
        if (iCurveClass->objectName().isEmpty())
            iCurveClass->setObjectName(QString::fromUtf8("iCurveClass"));
        iCurveClass->resize(650, 467);
        iCurveClass->setUnifiedTitleAndToolBarOnMac(false);
        actionOpen = new QAction(iCurveClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionClose = new QAction(iCurveClass);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionAbout = new QAction(iCurveClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionTitle = new QAction(iCurveClass);
        actionTitle->setObjectName(QString::fromUtf8("actionTitle"));
        actionSaveAs = new QAction(iCurveClass);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        centralwidget = new QWidget(iCurveClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        iCurveClass->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(iCurveClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        iCurveClass->setStatusBar(statusbar);
        menubar = new QMenuBar(iCurveClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 650, 18));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setTearOffEnabled(false);
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTitles = new QMenu(menubar);
        menuTitles->setObjectName(QString::fromUtf8("menuTitles"));
        iCurveClass->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTitles->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuHelp->addAction(actionAbout);
        menuTitles->addAction(actionTitle);

        retranslateUi(iCurveClass);

        QMetaObject::connectSlotsByName(iCurveClass);
    } // setupUi

    void retranslateUi(QMainWindow *iCurveClass)
    {
        iCurveClass->setWindowTitle(QApplication::translate("iCurveClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("iCurveClass", "Open", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("iCurveClass", "Close", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("iCurveClass", "about", 0, QApplication::UnicodeUTF8));
        actionTitle->setText(QApplication::translate("iCurveClass", "Title", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setText(QApplication::translate("iCurveClass", "Save as", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("iCurveClass", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("iCurveClass", "Help", 0, QApplication::UnicodeUTF8));
        menuTitles->setTitle(QApplication::translate("iCurveClass", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class iCurveClass: public Ui_iCurveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICURVE_H
