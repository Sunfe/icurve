#ifndef _EDIT_PLOT_DIALOG_H
#define _EDIT_PLOT_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QString>

#include <iCurve.h>

class iCurve;

class EditPlotDialog : public QDialog
{
    Q_OBJECT
    public:
        EditPlotDialog(QWidget * parent = 0,Qt::WindowFlags flag = 0);
        ~EditPlotDialog();
        QPushButton * createButton(const QString &title, const char * member);
        void submit();

        iCurve * figure();
        const iCurve* figure() const;


    protected:

        private slots:
            void accept ();
        void reject ();

    private:
        QLineEdit *plotTitle;
        QTabWidget *axisTab;
        QDialogButtonBox  *buttonBox;
};


#endif
