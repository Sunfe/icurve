#ifndef ICV_ABOUT_H
#define ICV_ABOUT_H

#include <Qt>
#include <QDialog>
#include <QWidget>
#include "ui_icv_about.h"

class IcvAboutDialog: public QDialog, public Ui::About
{
    Q_OBJECT
public:
    IcvAboutDialog(QWidget* parent);
    ~IcvAboutDialog(void);
};

#endif
