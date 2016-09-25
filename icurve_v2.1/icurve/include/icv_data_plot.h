#ifndef ICV_DATA_PLOT_H
#define ICV_DATA_PLOT_H

#include <QWidget>
#include <QPushButton>
#include "ui_icv_data_plot.h"

class IcvDataPlotDialog : public QDialog
{
    Q_OBJECT

public:
    IcvDataPlotDialog(QWidget *parent = 0);
    ~IcvDataPlotDialog();
public:
    QString getDataSting();
    void saveBlockData();
private slots:
        void processClickEvent();
signals:
        void sigPlotBlockData(QString data);
  
private:
    Ui::IcvDataPlotDialog ui;
    QAction *plotAction;
    QAction *clearAction;
    QAction *saveAction;
};

#endif // ICV_DATA_PLOT_H
