/********************************************************************************
** Form generated from reading UI file 'icv_curve_info.ui'
**
** Created: Wed Jun 22 00:39:22 2016
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
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_IcvCurveInfo
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *line;
    QFrame *line_2;
    QPlainTextEdit *plainEditFileBriefInfo;
    QComboBox *comboBoxCurveTitle;
    QPlainTextEdit *plainTextEditFilePos;

    void setupUi(QDialog *IcvCurveInfo)
    {
        if (IcvCurveInfo->objectName().isEmpty())
            IcvCurveInfo->setObjectName(QString::fromUtf8("IcvCurveInfo"));
        IcvCurveInfo->resize(468, 327);
        IcvCurveInfo->setSizeGripEnabled(false);
        buttonBox = new QDialogButtonBox(IcvCurveInfo);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(370, 290, 81, 32));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        label = new QLabel(IcvCurveInfo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(21, 15, 71, 21));
        label_2 = new QLabel(IcvCurveInfo);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 53, 91, 21));
        label_3 = new QLabel(IcvCurveInfo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 150, 81, 31));
        line = new QFrame(IcvCurveInfo);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 40, 431, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(IcvCurveInfo);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(20, 140, 431, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        plainEditFileBriefInfo = new QPlainTextEdit(IcvCurveInfo);
        plainEditFileBriefInfo->setObjectName(QString::fromUtf8("plainEditFileBriefInfo"));
        plainEditFileBriefInfo->setGeometry(QRect(110, 163, 341, 111));
        comboBoxCurveTitle = new QComboBox(IcvCurveInfo);
        comboBoxCurveTitle->setObjectName(QString::fromUtf8("comboBoxCurveTitle"));
        comboBoxCurveTitle->setGeometry(QRect(110, 20, 191, 22));
        plainTextEditFilePos = new QPlainTextEdit(IcvCurveInfo);
        plainTextEditFilePos->setObjectName(QString::fromUtf8("plainTextEditFilePos"));
        plainTextEditFilePos->setGeometry(QRect(110, 58, 341, 81));

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
    } // retranslateUi

};

namespace Ui {
    class IcvCurveInfo: public Ui_IcvCurveInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICV_CURVE_INFO_H
