#ifndef ICV_AXSE_SCALE_H
#define ICV_AXSE_SCALE_H

#include <QDialog>
#include <QString>
#include "ui_icv_axse_scale.h"

class IcvAxseSCaleDialog : public QDialog, public Ui::AxseScaleDialog
{
    Q_OBJECT

public:
    IcvAxseSCaleDialog(QWidget* parent=0);
    ~IcvAxseSCaleDialog(void);


    private slots:
        void accept();
        void reject();
};

#endif
