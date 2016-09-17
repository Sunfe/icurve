/********************************************************************************
** Form generated from reading UI file 'icv_curve_filter.ui'
**
** Created: Sat Sep 17 21:24:44 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICV_CURVE_FILTER_H
#define UI_ICV_CURVE_FILTER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_IcvCurveFilterDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QRadioButton *radioComandName;
    QRadioButton *radioLineId;
    QRadioButton *radioDirection;
    QRadioButton *radioCompleteComand;
    QRadioButton *radioPromt;
    QLabel *label;
    QCheckBox *previewCheckBox;
    QCheckBox *checkBox;

    void setupUi(QDialog *IcvCurveFilterDialog)
    {
        if (IcvCurveFilterDialog->objectName().isEmpty())
            IcvCurveFilterDialog->setObjectName(QString::fromUtf8("IcvCurveFilterDialog"));
        IcvCurveFilterDialog->resize(407, 230);
        buttonBox = new QDialogButtonBox(IcvCurveFilterDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(120, 184, 171, 32));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(IcvCurveFilterDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(87, 117, 291, 20));
        groupBox = new QGroupBox(IcvCurveFilterDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 361, 91));
        radioComandName = new QRadioButton(groupBox);
        radioComandName->setObjectName(QString::fromUtf8("radioComandName"));
        radioComandName->setGeometry(QRect(24, 23, 51, 20));
        radioLineId = new QRadioButton(groupBox);
        radioLineId->setObjectName(QString::fromUtf8("radioLineId"));
        radioLineId->setGeometry(QRect(120, 21, 61, 20));
        radioDirection = new QRadioButton(groupBox);
        radioDirection->setObjectName(QString::fromUtf8("radioDirection"));
        radioDirection->setGeometry(QRect(244, 20, 81, 20));
        radioCompleteComand = new QRadioButton(groupBox);
        radioCompleteComand->setObjectName(QString::fromUtf8("radioCompleteComand"));
        radioCompleteComand->setGeometry(QRect(120, 60, 121, 20));
        radioPromt = new QRadioButton(groupBox);
        radioPromt->setObjectName(QString::fromUtf8("radioPromt"));
        radioPromt->setGeometry(QRect(24, 60, 61, 20));
        label = new QLabel(IcvCurveFilterDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(27, 120, 54, 12));
        previewCheckBox = new QCheckBox(IcvCurveFilterDialog);
        previewCheckBox->setObjectName(QString::fromUtf8("previewCheckBox"));
        previewCheckBox->setGeometry(QRect(223, 149, 71, 20));
        checkBox = new QCheckBox(IcvCurveFilterDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(143, 150, 72, 17));

        retranslateUi(IcvCurveFilterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), IcvCurveFilterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IcvCurveFilterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(IcvCurveFilterDialog);
    } // setupUi

    void retranslateUi(QDialog *IcvCurveFilterDialog)
    {
        IcvCurveFilterDialog->setWindowTitle(QApplication::translate("IcvCurveFilterDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("IcvCurveFilterDialog", "Select:", 0, QApplication::UnicodeUTF8));
        radioComandName->setText(QApplication::translate("IcvCurveFilterDialog", "Name", 0, QApplication::UnicodeUTF8));
        radioLineId->setText(QApplication::translate("IcvCurveFilterDialog", "Line id", 0, QApplication::UnicodeUTF8));
        radioDirection->setText(QApplication::translate("IcvCurveFilterDialog", "Direction", 0, QApplication::UnicodeUTF8));
        radioCompleteComand->setText(QApplication::translate("IcvCurveFilterDialog", "Complete command", 0, QApplication::UnicodeUTF8));
        radioPromt->setText(QApplication::translate("IcvCurveFilterDialog", "Promt", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IcvCurveFilterDialog", "Keywords:", 0, QApplication::UnicodeUTF8));
        previewCheckBox->setText(QApplication::translate("IcvCurveFilterDialog", "Preview", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("IcvCurveFilterDialog", "In All", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IcvCurveFilterDialog: public Ui_IcvCurveFilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICV_CURVE_FILTER_H
