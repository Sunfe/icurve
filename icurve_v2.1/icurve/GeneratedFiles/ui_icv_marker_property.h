/********************************************************************************
** Form generated from reading UI file 'icv_marker_property.ui'
**
** Created: Sat Sep 17 21:24:44 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICV_MARKER_PROPERTY_H
#define UI_ICV_MARKER_PROPERTY_H

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
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_IcvMarkerProperty
{
public:
    QLineEdit *sizeLineEdit;
    QLabel *colorLabel;
    QPushButton *btnMarkerPen;
    QPushButton *btnMarkerBrush;
    QDialogButtonBox *buttonBox;
    QComboBox *typeComboBox;
    QLabel *sizeLabel;
    QLabel *typeLabel;

    void setupUi(QDialog *IcvMarkerProperty)
    {
        if (IcvMarkerProperty->objectName().isEmpty())
            IcvMarkerProperty->setObjectName(QString::fromUtf8("IcvMarkerProperty"));
        IcvMarkerProperty->resize(340, 183);
        sizeLineEdit = new QLineEdit(IcvMarkerProperty);
        sizeLineEdit->setObjectName(QString::fromUtf8("sizeLineEdit"));
        sizeLineEdit->setGeometry(QRect(79, 65, 241, 20));
        colorLabel = new QLabel(IcvMarkerProperty);
        colorLabel->setObjectName(QString::fromUtf8("colorLabel"));
        colorLabel->setGeometry(QRect(29, 105, 36, 16));
        btnMarkerPen = new QPushButton(IcvMarkerProperty);
        btnMarkerPen->setObjectName(QString::fromUtf8("btnMarkerPen"));
        btnMarkerPen->setGeometry(QRect(140, 100, 50, 30));
        btnMarkerPen->setMaximumSize(QSize(50, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icurve/images/linecolor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMarkerPen->setIcon(icon);
        btnMarkerBrush = new QPushButton(IcvMarkerProperty);
        btnMarkerBrush->setObjectName(QString::fromUtf8("btnMarkerBrush"));
        btnMarkerBrush->setGeometry(QRect(80, 100, 50, 30));
        btnMarkerBrush->setMinimumSize(QSize(20, 20));
        btnMarkerBrush->setMaximumSize(QSize(50, 30));
        btnMarkerBrush->setLayoutDirection(Qt::LeftToRight);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icurve/images/floodfill.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMarkerBrush->setIcon(icon1);
        buttonBox = new QDialogButtonBox(IcvMarkerProperty);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(160, 150, 160, 25));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        typeComboBox = new QComboBox(IcvMarkerProperty);
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));
        typeComboBox->setGeometry(QRect(79, 25, 241, 20));
        typeComboBox->setLayoutDirection(Qt::LeftToRight);
        sizeLabel = new QLabel(IcvMarkerProperty);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));
        sizeLabel->setGeometry(QRect(30, 65, 30, 16));
        typeLabel = new QLabel(IcvMarkerProperty);
        typeLabel->setObjectName(QString::fromUtf8("typeLabel"));
        typeLabel->setGeometry(QRect(30, 25, 30, 16));
        typeLabel->setMaximumSize(QSize(40, 50));

        retranslateUi(IcvMarkerProperty);
        QObject::connect(buttonBox, SIGNAL(accepted()), IcvMarkerProperty, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IcvMarkerProperty, SLOT(reject()));

        QMetaObject::connectSlotsByName(IcvMarkerProperty);
    } // setupUi

    void retranslateUi(QDialog *IcvMarkerProperty)
    {
        IcvMarkerProperty->setWindowTitle(QApplication::translate("IcvMarkerProperty", "Dialog", 0, QApplication::UnicodeUTF8));
        colorLabel->setText(QApplication::translate("IcvMarkerProperty", "Color:", 0, QApplication::UnicodeUTF8));
        btnMarkerPen->setText(QApplication::translate("IcvMarkerProperty", "Pen", 0, QApplication::UnicodeUTF8));
        btnMarkerBrush->setText(QApplication::translate("IcvMarkerProperty", "Brush", 0, QApplication::UnicodeUTF8));
        typeComboBox->clear();
        typeComboBox->insertItems(0, QStringList()
         << QApplication::translate("IcvMarkerProperty", "Ellipse", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "Rect", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "Diamond", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "Triangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "DTriangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "UTriangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "LTriangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "RTriangle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "Cross(+)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "XCross(x)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "HLine", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "VLine", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "Star1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "Star2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("IcvMarkerProperty", "Hexagon", 0, QApplication::UnicodeUTF8)
        );
        sizeLabel->setText(QApplication::translate("IcvMarkerProperty", "Size:", 0, QApplication::UnicodeUTF8));
        typeLabel->setText(QApplication::translate("IcvMarkerProperty", "Type:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IcvMarkerProperty: public Ui_IcvMarkerProperty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICV_MARKER_PROPERTY_H
