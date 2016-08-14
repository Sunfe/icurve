/********************************************************************************
** Form generated from reading UI file 'icv_curve_info.ui'
**
** Created: Sun Aug 14 09:34:36 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICV_CURVE_INFO_H
#define UI_ICV_CURVE_INFO_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_IcvCurveInfo
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBoxCurveTitle;
    QPlainTextEdit *plainTextEditFilePos;
    QLabel *label_4;
    QLineEdit *lineEditPromt;
    QLabel *label_5;
    QLineEdit *lineEditGroupSize;
    QLineEdit *plainEditFileBriefInfo;

    void setupUi(QDialog *IcvCurveInfo)
    {
        if (IcvCurveInfo->objectName().isEmpty())
            IcvCurveInfo->setObjectName(QString::fromUtf8("IcvCurveInfo"));
        IcvCurveInfo->resize(471, 306);
        IcvCurveInfo->setSizeGripEnabled(false);
        buttonBox = new QDialogButtonBox(IcvCurveInfo);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(370, 270, 81, 32));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        label = new QLabel(IcvCurveInfo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(21, 17, 71, 21));
        label_2 = new QLabel(IcvCurveInfo);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 164, 91, 21));
        label_3 = new QLabel(IcvCurveInfo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 122, 81, 31));
        comboBoxCurveTitle = new QComboBox(IcvCurveInfo);
        comboBoxCurveTitle->setObjectName(QString::fromUtf8("comboBoxCurveTitle"));
        comboBoxCurveTitle->setGeometry(QRect(110, 20, 201, 22));
        plainTextEditFilePos = new QPlainTextEdit(IcvCurveInfo);
        plainTextEditFilePos->setObjectName(QString::fromUtf8("plainTextEditFilePos"));
        plainTextEditFilePos->setGeometry(QRect(110, 170, 341, 91));
        label_4 = new QLabel(IcvCurveInfo);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 51, 81, 21));
        lineEditPromt = new QLineEdit(IcvCurveInfo);
        lineEditPromt->setObjectName(QString::fromUtf8("lineEditPromt"));
        lineEditPromt->setGeometry(QRect(110, 53, 201, 20));
        lineEditPromt->setReadOnly(true);
        label_5 = new QLabel(IcvCurveInfo);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 88, 71, 20));
        lineEditGroupSize = new QLineEdit(IcvCurveInfo);
        lineEditGroupSize->setObjectName(QString::fromUtf8("lineEditGroupSize"));
        lineEditGroupSize->setGeometry(QRect(110, 90, 201, 20));
        lineEditGroupSize->setReadOnly(true);
        plainEditFileBriefInfo = new QLineEdit(IcvCurveInfo);
        plainEditFileBriefInfo->setObjectName(QString::fromUtf8("plainEditFileBriefInfo"));
        plainEditFileBriefInfo->setGeometry(QRect(110, 130, 341, 20));
        plainEditFileBriefInfo->setReadOnly(true);

        retranslateUi(IcvCurveInfo);
        QObject::connect(buttonBox, SIGNAL(accepted()), IcvCurveInfo, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IcvCurveInfo, SLOT(reject()));

        QMetaObject::connectSlotsByName(IcvCurveInfo);
    } // setupUi

    void retranslateUi(QDialog *IcvCurveInfo)
    {
        IcvCurveInfo->setWindowTitle(QApplication::translate("IcvCurveInfo", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IcvCurveInfo", "Curve Name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IcvCurveInfo", "File position:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("IcvCurveInfo", "Command info:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("IcvCurveInfo", "Promt:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("IcvCurveInfo", "Group Size:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IcvCurveInfo: public Ui_IcvCurveInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICV_CURVE_INFO_H
