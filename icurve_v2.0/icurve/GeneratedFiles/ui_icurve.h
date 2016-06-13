/********************************************************************************
** Form generated from reading UI file 'icurve.ui'
**
** Created: Tue Jun 14 01:04:48 2016
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
    QAction *actionSaveAs;
    QAction *actionDo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionRemove;
    QAction *actionSelectAll;
    QAction *actionX_label;
    QAction *actionY_label;
    QAction *actionTitle;
    QAction *actionClose;
    QAction *actionExit;
    QAction *actionColor;
    QAction *actionWidth;
    QAction *actionLegend;
    QAction *actionFooter;
    QAction *actionCalc;
    QAction *actionStyle;
    QAction *actionMarker;
    QAction *actionFilter;
    QAction *actionAxse_Properties;
    QAction *actionFind;
    QAction *actionShowAll;
    QAction *actionExpand;
    QAction *actionView_data;
    QAction *actionLocate_to_file;
    QAction *actionPreference;
    QAction *actionAbout;
    QAction *actionCurveName;
    QAction *actionDelete;
    QAction *actionDiffer;
    QAction *actionReset;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuTools;
    QMenu *menuWindows;
    QMenu *menuHelp_2;
    QMenu *menuCurve;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *icurveClass)
    {
        if (icurveClass->objectName().isEmpty())
            icurveClass->setObjectName(QString::fromUtf8("icurveClass"));
        icurveClass->resize(759, 475);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icurve/images/main.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icurveClass->setWindowIcon(icon);
        actionOpen = new QAction(icurveClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icurve/images/file_open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(icurveClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        actionSaveAs = new QAction(icurveClass);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionDo = new QAction(icurveClass);
        actionDo->setObjectName(QString::fromUtf8("actionDo"));
        actionDo->setEnabled(false);
        actionRedo = new QAction(icurveClass);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionRedo->setEnabled(false);
        actionCut = new QAction(icurveClass);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCut->setEnabled(false);
        actionCopy = new QAction(icurveClass);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionCopy->setEnabled(false);
        actionPaste = new QAction(icurveClass);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionPaste->setEnabled(false);
        actionRemove = new QAction(icurveClass);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
        actionRemove->setEnabled(true);
        actionSelectAll = new QAction(icurveClass);
        actionSelectAll->setObjectName(QString::fromUtf8("actionSelectAll"));
        actionSelectAll->setEnabled(true);
        actionX_label = new QAction(icurveClass);
        actionX_label->setObjectName(QString::fromUtf8("actionX_label"));
        actionY_label = new QAction(icurveClass);
        actionY_label->setObjectName(QString::fromUtf8("actionY_label"));
        actionTitle = new QAction(icurveClass);
        actionTitle->setObjectName(QString::fromUtf8("actionTitle"));
        actionClose = new QAction(icurveClass);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClose->setEnabled(false);
        actionExit = new QAction(icurveClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionColor = new QAction(icurveClass);
        actionColor->setObjectName(QString::fromUtf8("actionColor"));
        actionWidth = new QAction(icurveClass);
        actionWidth->setObjectName(QString::fromUtf8("actionWidth"));
        actionLegend = new QAction(icurveClass);
        actionLegend->setObjectName(QString::fromUtf8("actionLegend"));
        actionLegend->setCheckable(true);
        actionFooter = new QAction(icurveClass);
        actionFooter->setObjectName(QString::fromUtf8("actionFooter"));
        actionCalc = new QAction(icurveClass);
        actionCalc->setObjectName(QString::fromUtf8("actionCalc"));
        actionStyle = new QAction(icurveClass);
        actionStyle->setObjectName(QString::fromUtf8("actionStyle"));
        actionMarker = new QAction(icurveClass);
        actionMarker->setObjectName(QString::fromUtf8("actionMarker"));
        actionFilter = new QAction(icurveClass);
        actionFilter->setObjectName(QString::fromUtf8("actionFilter"));
        actionFilter->setCheckable(false);
        actionAxse_Properties = new QAction(icurveClass);
        actionAxse_Properties->setObjectName(QString::fromUtf8("actionAxse_Properties"));
        actionFind = new QAction(icurveClass);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        actionShowAll = new QAction(icurveClass);
        actionShowAll->setObjectName(QString::fromUtf8("actionShowAll"));
        actionExpand = new QAction(icurveClass);
        actionExpand->setObjectName(QString::fromUtf8("actionExpand"));
        actionView_data = new QAction(icurveClass);
        actionView_data->setObjectName(QString::fromUtf8("actionView_data"));
        actionView_data->setEnabled(false);
        actionLocate_to_file = new QAction(icurveClass);
        actionLocate_to_file->setObjectName(QString::fromUtf8("actionLocate_to_file"));
        actionLocate_to_file->setEnabled(false);
        actionPreference = new QAction(icurveClass);
        actionPreference->setObjectName(QString::fromUtf8("actionPreference"));
        actionAbout = new QAction(icurveClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionCurveName = new QAction(icurveClass);
        actionCurveName->setObjectName(QString::fromUtf8("actionCurveName"));
        actionCurveName->setCheckable(true);
        actionCurveName->setChecked(false);
        actionCurveName->setEnabled(true);
        actionDelete = new QAction(icurveClass);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionDiffer = new QAction(icurveClass);
        actionDiffer->setObjectName(QString::fromUtf8("actionDiffer"));
        actionReset = new QAction(icurveClass);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        centralWidget = new QWidget(icurveClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        icurveClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(icurveClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 759, 17));
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
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
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
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuBar->addAction(menuHelp_2->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionDo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionReset);
        menuEdit->addSeparator();
        menuEdit->addAction(actionRemove);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionFind);
        menuEdit->addAction(actionShowAll);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelectAll);
        menuHelp->addAction(actionTitle);
        menuHelp->addAction(actionX_label);
        menuHelp->addAction(actionY_label);
        menuHelp->addSeparator();
        menuHelp->addAction(actionLegend);
        menuHelp->addSeparator();
        menuHelp->addAction(actionCurveName);
        menuHelp->addSeparator();
        menuHelp->addAction(actionFooter);
        menuTools->addAction(actionCalc);
        menuTools->addAction(actionDiffer);
        menuHelp_2->addAction(actionAbout);
        menuCurve->addAction(actionColor);
        menuCurve->addAction(actionWidth);
        menuCurve->addAction(actionStyle);
        menuCurve->addAction(actionMarker);
        menuCurve->addAction(actionExpand);
        menuCurve->addAction(actionFilter);
        menuCurve->addAction(actionView_data);
        menuCurve->addAction(actionLocate_to_file);
        menuOptions->addAction(actionPreference);
        menuOptions->addAction(actionAxse_Properties);
        mainToolBar->addAction(actionOpen);

        retranslateUi(icurveClass);

        QMetaObject::connectSlotsByName(icurveClass);
    } // setupUi

    void retranslateUi(QMainWindow *icurveClass)
    {
        icurveClass->setWindowTitle(QApplication::translate("icurveClass", "icurve", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("icurveClass", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("icurveClass", "Save", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setText(QApplication::translate("icurveClass", "Save as", 0, QApplication::UnicodeUTF8));
        actionDo->setText(QApplication::translate("icurveClass", "Undo", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("icurveClass", "Redo", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("icurveClass", "Cut", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("icurveClass", "Copy", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("icurveClass", "Paste", 0, QApplication::UnicodeUTF8));
        actionRemove->setText(QApplication::translate("icurveClass", "Remove", 0, QApplication::UnicodeUTF8));
        actionSelectAll->setText(QApplication::translate("icurveClass", "Select All", 0, QApplication::UnicodeUTF8));
        actionX_label->setText(QApplication::translate("icurveClass", "X Label", 0, QApplication::UnicodeUTF8));
        actionY_label->setText(QApplication::translate("icurveClass", "Y Label", 0, QApplication::UnicodeUTF8));
        actionTitle->setText(QApplication::translate("icurveClass", "Plot Title", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("icurveClass", "Close", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("icurveClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionColor->setText(QApplication::translate("icurveClass", "Color", 0, QApplication::UnicodeUTF8));
        actionWidth->setText(QApplication::translate("icurveClass", "Width", 0, QApplication::UnicodeUTF8));
        actionLegend->setText(QApplication::translate("icurveClass", "Legend", 0, QApplication::UnicodeUTF8));
        actionFooter->setText(QApplication::translate("icurveClass", "Footer", 0, QApplication::UnicodeUTF8));
        actionCalc->setText(QApplication::translate("icurveClass", "Calculator", 0, QApplication::UnicodeUTF8));
        actionStyle->setText(QApplication::translate("icurveClass", "Style", 0, QApplication::UnicodeUTF8));
        actionMarker->setText(QApplication::translate("icurveClass", "Marker", 0, QApplication::UnicodeUTF8));
        actionFilter->setText(QApplication::translate("icurveClass", "Filter", 0, QApplication::UnicodeUTF8));
        actionAxse_Properties->setText(QApplication::translate("icurveClass", "Axse", 0, QApplication::UnicodeUTF8));
        actionFind->setText(QApplication::translate("icurveClass", "Find", 0, QApplication::UnicodeUTF8));
        actionShowAll->setText(QApplication::translate("icurveClass", "Show All", 0, QApplication::UnicodeUTF8));
        actionExpand->setText(QApplication::translate("icurveClass", "Expand", 0, QApplication::UnicodeUTF8));
        actionView_data->setText(QApplication::translate("icurveClass", "View data", 0, QApplication::UnicodeUTF8));
        actionLocate_to_file->setText(QApplication::translate("icurveClass", "Jump to file", 0, QApplication::UnicodeUTF8));
        actionPreference->setText(QApplication::translate("icurveClass", "Preference...", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("icurveClass", "About", 0, QApplication::UnicodeUTF8));
        actionCurveName->setText(QApplication::translate("icurveClass", "Curve Name", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("icurveClass", "Delete", 0, QApplication::UnicodeUTF8));
        actionDiffer->setText(QApplication::translate("icurveClass", "Differ", 0, QApplication::UnicodeUTF8));
        actionReset->setText(QApplication::translate("icurveClass", "Reset", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("icurveClass", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("icurveClass", "Edit", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("icurveClass", "Insert", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("icurveClass", "Tools", 0, QApplication::UnicodeUTF8));
        menuWindows->setTitle(QApplication::translate("icurveClass", "Windows", 0, QApplication::UnicodeUTF8));
        menuHelp_2->setTitle(QApplication::translate("icurveClass", "Help", 0, QApplication::UnicodeUTF8));
        menuCurve->setTitle(QApplication::translate("icurveClass", "Curve", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("icurveClass", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class icurveClass: public Ui_icurveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICURVE_H
