/********************************************************************************
** Form generated from reading UI file 'icv_axse_scale.ui'
**
** Created: Sat Jun 25 21:09:34 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICV_AXSE_SCALE_H
#define UI_ICV_AXSE_SCALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_AxseScaleDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLineEdit *lineEditMinX;
    QLineEdit *lineEditMaxX;
    QLabel *label_2;
    QLabel *label;
    QGroupBox *groupBox_2;
    QLineEdit *lineEditMaxY;
    QLineEdit *lineEditMinY;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QDialog *AxseScaleDialog)
    {
        if (AxseScaleDialog->objectName().isEmpty())
            AxseScaleDialog->setObjectName(QString::fromUtf8("AxseScaleDialog"));
        AxseScaleDialog->resize(235, 202);
        AxseScaleDialog->setFocusPolicy(Qt::TabFocus);
        buttonBox = new QDialogButtonBox(AxseScaleDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(63, 165, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(AxseScaleDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(13, 10, 211, 71));
        lineEditMinX = new QLineEdit(groupBox);
        lineEditMinX->setObjectName(QString::fromUtf8("lineEditMinX"));
        lineEditMinX->setGeometry(QRect(11, 33, 70, 20));
        lineEditMaxX = new QLineEdit(groupBox);
        lineEditMaxX->setObjectName(QString::fromUtf8("lineEditMaxX"));
        lineEditMaxX->setGeometry(QRect(117, 33, 70, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(119, 16, 41, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(12, 14, 41, 20));
        groupBox_2 = new QGroupBox(AxseScaleDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(13, 90, 211, 71));
        groupBox_2->setFocusPolicy(Qt::NoFocus);
        lineEditMaxY = new QLineEdit(groupBox_2);
        lineEditMaxY->setObjectName(QString::fromUtf8("lineEditMaxY"));
        lineEditMaxY->setGeometry(QRect(117, 33, 70, 20));
        lineEditMinY = new QLineEdit(groupBox_2);
        lineEditMinY->setObjectName(QString::fromUtf8("lineEditMinY"));
        lineEditMinY->setGeometry(QRect(11, 33, 70, 20));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(120, 15, 41, 16));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(13, 14, 41, 20));
        lineEditMaxY->raise();
        label_7->raise();
        label_8->raise();
        lineEditMinY->raise();

        retranslateUi(AxseScaleDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AxseScaleDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AxseScaleDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AxseScaleDialog);
    } // setupUi

    void retranslateUi(QDialog *AxseScaleDialog)
    {
        AxseScaleDialog->setWindowTitle(QApplication::translate("AxseScaleDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AxseScaleDialog", "X Range:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AxseScaleDialog", "Max:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AxseScaleDialog", "Min:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("AxseScaleDialog", "Y Range:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("AxseScaleDialog", "Max:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("AxseScaleDialog", "Min:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AxseScaleDialog: public Ui_AxseScaleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICV_AXSE_SCALE_H
