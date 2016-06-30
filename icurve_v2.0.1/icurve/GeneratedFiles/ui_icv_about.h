/********************************************************************************
** Form generated from reading UI file 'icv_about.ui'
**
** Created: Fri Jul 1 01:03:38 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICV_ABOUT_H
#define UI_ICV_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(378, 188);
        label = new QLabel(About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 50, 121, 31));
        label_2 = new QLabel(About);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 100, 191, 31));

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "About", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("About", "Author:Liao.ZhiCheng", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("About", "Copyright: DSL team, ZTE, 2016.6", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICV_ABOUT_H
