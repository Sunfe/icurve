
#include <QMessageBox>
#include <editPlotDialog.h>
#include <qwt_plot.h>


    EditPlotDialog::EditPlotDialog(QWidget * parent,Qt::WindowFlags flag)
: QDialog(parent,flag)
{
    setModal(false);

    /*{{{plot title*/
    QLabel *titleLa = new QLabel("Plot title:");
    plotTitle =  new QLineEdit(this);
    plotTitle->setText(figure()->getPlot()->title().text());
    plotTitle->setFocus();
    titleLa->setBuddy(plotTitle);
    /*}}}*/

    /*{{{axis tab*/
    /*tab layout*/
    QLabel *labelX = new QLabel("title:");
    QLineEdit *editX =  new QLineEdit(this);
    editX->setObjectName(tr("editX"));
    editX->setText(figure()->getPlot()->axisTitle(QwtPlot::xBottom).text());
    labelX->setBuddy(editX);

    QLayout *tabLayoutX = new QVBoxLayout;
    tabLayoutX->addWidget(labelX);
    tabLayoutX->addWidget(editX);
    tabLayoutX->setAlignment(Qt::AlignTop);


    QLabel *labelY = new QLabel("title:");
    QLineEdit *editY =  new QLineEdit(this);
    editY->setObjectName(tr("editY"));
    editY->setText(figure()->getPlot()->axisTitle(QwtPlot::yLeft).text());
    labelY->setBuddy(editY);

    QLayout *tabLayoutY = new QVBoxLayout;
    tabLayoutY->addWidget(labelY);
    tabLayoutY->addWidget(editY);
    tabLayoutY->setAlignment(Qt::AlignTop);

    /*add x & y layout to QTabWidget*/
    axisTab = new QTabWidget(this);
    axisTab->setObjectName(tr("axisTab"));

    QWidget *axisX = new QWidget(axisTab);
    axisX->setLayout ( tabLayoutX );
    axisX->setObjectName(tr("axisX"));

    QWidget *axisY = new QWidget(axisTab);
    axisY->setLayout ( tabLayoutY );
    axisY->setObjectName(tr("axisY"));


    axisTab->addTab(axisX, tr("X"));
    axisTab->addTab(axisY, tr("Y"));

    /*}}}*/

    /*{{{button*/
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok \
            |QDialogButtonBox::Cancel);
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(buttonBox);
    /*}}}*/

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(titleLa,0,0);
    layout->addWidget(plotTitle,0,1);
    layout->addWidget(axisTab,1,0,1,2);
    layout->addLayout(btnLayout,2,0,1,2);
    layout->setAlignment(Qt::AlignTop);

    setLayout(layout);


}

QPushButton * EditPlotDialog::createButton(const QString &title, const char * member)
{
    QPushButton *button = new QPushButton(title,this);
    connect(button,SIGNAL(clicked()),this, SLOT(member));
    return button;
}



void EditPlotDialog::submit()
{	    
    return;
}


iCurve* EditPlotDialog:: figure()
{
    return qobject_cast < iCurve * >(parent());
}

const iCurve* EditPlotDialog:: figure() const
{
    return qobject_cast < const iCurve * >(parent());

}

void EditPlotDialog::accept()
{

    QwtPlot* plot = figure()->getPlot();
    QString title = plotTitle->text();
    plot->setTitle(title);

    QLineEdit *editX = findChild<QLineEdit *>(tr("editX"));
    QLineEdit *editY = findChild<QLineEdit *>(tr("editY"));

    plot->setAxisTitle(QwtPlot::xBottom, editX->text());
    plot->setAxisTitle(QwtPlot::yLeft, editY->text());
    plot->replot();

    return QDialog::accept ();
}

void EditPlotDialog::reject()
{
    return QDialog::reject ();
}

EditPlotDialog::~EditPlotDialog()
{

}

