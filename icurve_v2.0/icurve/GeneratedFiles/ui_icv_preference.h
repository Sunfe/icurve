/********************************************************************************
** Form generated from reading UI file 'icv_preference.ui'
**
** Created: Thu Jun 23 18:33:11 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICV_PREFERENCE_H
#define UI_ICV_PREFERENCE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Preference
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *legend;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *tab_2;
    QLabel *label_2;
    QWidget *tab;

    void setupUi(QDialog *Preference)
    {
        if (Preference->objectName().isEmpty())
            Preference->setObjectName(QString::fromUtf8("Preference"));
        Preference->resize(664, 457);
        buttonBox = new QDialogButtonBox(Preference);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(280, 410, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(Preference);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 661, 401));
        legend = new QWidget();
        legend->setObjectName(QString::fromUtf8("legend"));
        label = new QLabel(legend);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 61, 16));
        comboBox = new QComboBox(legend);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(90, 30, 74, 22));
        tabWidget->addTab(legend, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 20, 141, 16));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());

        retranslateUi(Preference);
        QObject::connect(buttonBox, SIGNAL(accepted()), Preference, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Preference, SLOT(reject()));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Preference);
    } // setupUi

    void retranslateUi(QDialog *Preference)
    {
        Preference->setWindowTitle(QApplication::translate("Preference", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Preference", "Position:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Preference", "Left", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Preference", "Right", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Preference", "Bottom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Preference", "Top", 0, QApplication::UnicodeUTF8)
        );
        tabWidget->setTabText(tabWidget->indexOf(legend), QApplication::translate("Preference", "Legend", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Preference", "Canvas", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Preference", "Magnifier", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Preference: public Ui_Preference {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICV_PREFERENCE_H
