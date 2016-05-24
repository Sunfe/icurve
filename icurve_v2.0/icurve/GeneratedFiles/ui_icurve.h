/********************************************************************************
** Form generated from reading UI file 'icurve.ui'
**
** Created: Wed May 25 00:18:36 2016
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
    QAction *actionClose;
    QAction *actionDo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClear;
    QAction *actionSelect_all;
    QAction *actionAxsi;
    QAction *actionX_lable;
    QAction *actionY_lable;
    QAction *actionTitle;
    QAction *actionLegand;
    QAction *actionExit;
    QAction *actionExit_2;
    QAction *actionColor;
    QAction *actionStyle;
    QAction *actionStyle_2;
    QAction *actionType;
    QAction *actionSize;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuTools;
    QMenu *menuWindows;
    QMenu *menuHelp_2;
    QMenu *menuCurve;
    QMenu *menuMarker;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *icurveClass)
    {
        if (icurveClass->objectName().isEmpty())
            icurveClass->setObjectName(QString::fromUtf8("icurveClass"));
        icurveClass->resize(538, 456);
        actionOpen = new QAction(icurveClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icurve/images/file_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionSave = new QAction(icurveClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionClose = new QAction(icurveClass);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionDo = new QAction(icurveClass);
        actionDo->setObjectName(QString::fromUtf8("actionDo"));
        actionRedo = new QAction(icurveClass);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionCut = new QAction(icurveClass);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCopy = new QAction(icurveClass);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(icurveClass);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionClear = new QAction(icurveClass);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionSelect_all = new QAction(icurveClass);
        actionSelect_all->setObjectName(QString::fromUtf8("actionSelect_all"));
        actionAxsi = new QAction(icurveClass);
        actionAxsi->setObjectName(QString::fromUtf8("actionAxsi"));
        actionX_lable = new QAction(icurveClass);
        actionX_lable->setObjectName(QString::fromUtf8("actionX_lable"));
        actionY_lable = new QAction(icurveClass);
        actionY_lable->setObjectName(QString::fromUtf8("actionY_lable"));
        actionTitle = new QAction(icurveClass);
        actionTitle->setObjectName(QString::fromUtf8("actionTitle"));
        actionLegand = new QAction(icurveClass);
        actionLegand->setObjectName(QString::fromUtf8("actionLegand"));
        actionExit = new QAction(icurveClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionExit_2 = new QAction(icurveClass);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        actionColor = new QAction(icurveClass);
        actionColor->setObjectName(QString::fromUtf8("actionColor"));
        actionStyle = new QAction(icurveClass);
        actionStyle->setObjectName(QString::fromUtf8("actionStyle"));
        actionStyle_2 = new QAction(icurveClass);
        actionStyle_2->setObjectName(QString::fromUtf8("actionStyle_2"));
        actionType = new QAction(icurveClass);
        actionType->setObjectName(QString::fromUtf8("actionType"));
        actionSize = new QAction(icurveClass);
        actionSize->setObjectName(QString::fromUtf8("actionSize"));
        centralWidget = new QWidget(icurveClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        icurveClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(icurveClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 538, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
        menuHelp_2 = new QMenu(menuBar);
        menuHelp_2->setObjectName(QString::fromUtf8("menuHelp_2"));
        menuCurve = new QMenu(menuBar);
        menuCurve->setObjectName(QString::fromUtf8("menuCurve"));
        menuMarker = new QMenu(menuCurve);
        menuMarker->setObjectName(QString::fromUtf8("menuMarker"));
        icurveClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(icurveClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(85, 170, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        QBrush brush3(QColor(106, 104, 100, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        mainToolBar->setPalette(palette);
        mainToolBar->setCursor(QCursor(Qt::ArrowCursor));
        mainToolBar->setMovable(false);
        mainToolBar->setAllowedAreas(Qt::TopToolBarArea);
        mainToolBar->setIconSize(QSize(24, 24));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        mainToolBar->setFloatable(false);
        icurveClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(icurveClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        icurveClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuCurve->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuBar->addAction(menuHelp_2->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuFile->addAction(actionExit_2);
        menuEdit->addAction(actionDo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionClear);
        menuEdit->addAction(actionSelect_all);
        menuEdit->addSeparator();
        menuEdit->addAction(actionAxsi);
        menuHelp->addAction(actionX_lable);
        menuHelp->addAction(actionY_lable);
        menuHelp->addSeparator();
        menuHelp->addAction(actionTitle);
        menuHelp->addSeparator();
        menuHelp->addAction(actionLegand);
        menuCurve->addAction(actionColor);
        menuCurve->addAction(actionStyle);
        menuCurve->addAction(actionStyle_2);
        menuCurve->addAction(menuMarker->menuAction());
        menuMarker->addAction(actionType);
        menuMarker->addAction(actionSize);
        mainToolBar->addAction(actionOpen);

        retranslateUi(icurveClass);

        QMetaObject::connectSlotsByName(icurveClass);
    } // setupUi

    void retranslateUi(QMainWindow *icurveClass)
    {
        icurveClass->setWindowTitle(QApplication::translate("icurveClass", "icurve", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("icurveClass", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("icurveClass", "Save", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("icurveClass", "Save as", 0, QApplication::UnicodeUTF8));
        actionDo->setText(QApplication::translate("icurveClass", "Undo", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("icurveClass", "Redo", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("icurveClass", "Cut", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("icurveClass", "Copy", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("icurveClass", "Paste", 0, QApplication::UnicodeUTF8));
        actionClear->setText(QApplication::translate("icurveClass", "Clear", 0, QApplication::UnicodeUTF8));
        actionSelect_all->setText(QApplication::translate("icurveClass", "Select All", 0, QApplication::UnicodeUTF8));
        actionAxsi->setText(QApplication::translate("icurveClass", "Axse Properties", 0, QApplication::UnicodeUTF8));
        actionX_lable->setText(QApplication::translate("icurveClass", "X lable", 0, QApplication::UnicodeUTF8));
        actionY_lable->setText(QApplication::translate("icurveClass", "Y lable", 0, QApplication::UnicodeUTF8));
        actionTitle->setText(QApplication::translate("icurveClass", "Title", 0, QApplication::UnicodeUTF8));
        actionLegand->setText(QApplication::translate("icurveClass", "Legend", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("icurveClass", "Close", 0, QApplication::UnicodeUTF8));
        actionExit_2->setText(QApplication::translate("icurveClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionColor->setText(QApplication::translate("icurveClass", "Color", 0, QApplication::UnicodeUTF8));
        actionStyle->setText(QApplication::translate("icurveClass", "Width", 0, QApplication::UnicodeUTF8));
        actionStyle_2->setText(QApplication::translate("icurveClass", "Style", 0, QApplication::UnicodeUTF8));
        actionType->setText(QApplication::translate("icurveClass", "Type", 0, QApplication::UnicodeUTF8));
        actionSize->setText(QApplication::translate("icurveClass", "Size", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("icurveClass", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("icurveClass", "Edit", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("icurveClass", "Insert", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("icurveClass", "Tools", 0, QApplication::UnicodeUTF8));
        menuWindows->setTitle(QApplication::translate("icurveClass", "Windows", 0, QApplication::UnicodeUTF8));
        menuHelp_2->setTitle(QApplication::translate("icurveClass", "Help", 0, QApplication::UnicodeUTF8));
        menuCurve->setTitle(QApplication::translate("icurveClass", "Curve", 0, QApplication::UnicodeUTF8));
        menuMarker->setTitle(QApplication::translate("icurveClass", "Marker", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class icurveClass: public Ui_icurveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICURVE_H
