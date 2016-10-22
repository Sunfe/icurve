#ifndef ICV_CLIPARSER_DIALOG_H
#define ICV_CLIPARSER_DIALOG_H

#include <QDialog>
#include <QTextEdit>
#include "ui_icv_cli_parser.h"

class IcvCliParserDialog : public QDialog
{
    Q_OBJECT

public:
    IcvCliParserDialog(QWidget *parent = 0);
    ~IcvCliParserDialog();

public slots:
    void parzeHex(bool);
    void clear();
    void save();

private:
    Ui::CliParserDialog ui;
    QAction *plotAction;
    QAction *clearAction;
    QAction *saveAction;
    QAction *exportAction;
    QTextEdit *orig; 
    QTextEdit *target;
};

#endif // ICV_CLIPARSER_DIALOG_H
