#include <QColorDialog>
#include <QMessageBox>
#include <qwt_plot.h>
#include "icv_curve_property.h"
#include "icv_penstyle.h"


IcvCurvePropertyDialog::IcvCurvePropertyDialog(IcvPlotCurve *crv, QWidget * parent,
    Qt::WindowFlags flag) : QDialog(parent,flag)
{
    int currentIndex = 0;

    if(NULL == crv)
        return;

    curve = crv;
    if(NULL == curve->getCurve())
        return ;

    curveStyle  = curve->getCurve()->pen().style();
    curveWidth  = curve->getCurve()->pen().width();
    curveColor  = curve->getCurve()->pen().color();
    curveTitile = curve->getCurve()->title();

    QList<QwtPlotMarker *> markers = curve->getMarkers();
    if( QwtSymbol::NoSymbol != markers[0]->symbol()->style())
    {
        markerStyle = markers[0]->symbol()->style();
        markerBrush = markers[0]->symbol()->brush();
        markerPen   = markers[0]->symbol()->pen();
        markerSize  = markers[0]->symbol()->size();
    }
    else
    {
        markerStyle = QwtSymbol::NoSymbol;
        markerBrush = QBrush(Qt::black);
        markerPen   = QPen(Qt::black);
        markerSize  = QSize(1,1);
    }

    /*disable all changes from the mainWindow*/
    setModal(true);

    /*initialize Object*/
    /*{{{curve*/
    nameLabel = new QLabel("Display Name:");
    nameText = new QLineEdit(this);
    nameText->setText(curveTitile.text());
    nameText->setFocus();
    nameLabel->setBuddy(nameText);

    lineLabel = new QLabel("Line:");
    lineTypeCombox = new QComboBox(this);
    lineTypeCombox->setItemDelegate(new IcvPenStyleDelegate((QObject *)lineTypeCombox));
    lineTypeCombox->addItem(tr("Solid")   , Qt::SolidLine);
    lineTypeCombox->addItem(tr("Dash") , Qt::DashDotLine);
    lineTypeCombox->addItem(tr("Dot")     , Qt::DotLine);
    lineTypeCombox->addItem(tr("DashDot") , Qt::DashDotLine);
    lineTypeCombox->addItem(tr("DashDotDot"),Qt::DashDotDotLine);
    currentIndex = static_cast<int>(curveStyle - 1);  /*combox index stared with 0*/
    lineTypeCombox->setCurrentIndex((currentIndex));
    connect(lineTypeCombox,SIGNAL(activated(int)), this, SLOT(setCurveStyle(int)));


    curveWidthCombox = new QComboBox(this);
    curveWidthCombox->addItem("0.5");
    curveWidthCombox->addItem("1");
    curveWidthCombox->addItem("2");
    curveWidthCombox->addItem("3");
    curveWidthCombox->addItem("4");
    curveWidthCombox->addItem("6");
    curveWidthCombox->addItem("8");
    curveWidthCombox->addItem("10");
    curveWidthCombox->setEditable(true);
    curveWidthCombox->lineEdit()->setText(QString::number(curveWidth));
    connect(curveWidthCombox,SIGNAL(activated(int)), this, SLOT(setCurveWidth(int)));


    btnLineColor = new QPushButton(this);
    btnLineColor->setIcon(createColorToolButtonIcon(tr("images/linecolor.png"),curveColor));
    connect(btnLineColor,SIGNAL(clicked()), this, SLOT(setCurveColor()));
    /*}}}*/

    /*{{{ maker*/
    /*marker style*/
    markerLabel = new QLabel("Marker:");
    markerTypeCombox = new QComboBox(this);
    markerTypeCombox->addItem("None");
    markerTypeCombox->addItem("Ellipse");
    markerTypeCombox->addItem("Rect");
    markerTypeCombox->addItem("Diamond");
    markerTypeCombox->addItem("Triangle");
    markerTypeCombox->addItem("DTriangle");
    markerTypeCombox->addItem("LTriangle");
    markerTypeCombox->addItem("Ellipse");
    markerTypeCombox->addItem("RTriangle");
    markerTypeCombox->addItem("Cross(+)");
    markerTypeCombox->addItem("XCross(x)");
    markerTypeCombox->addItem("HLine");
    markerTypeCombox->addItem("VLine");
    markerTypeCombox->addItem("Star1");
    markerTypeCombox->addItem("Star2");
    markerTypeCombox->addItem("Hexagon");
    currentIndex = static_cast<int>( markerStyle + 1 );
    markerTypeCombox->setCurrentIndex((currentIndex));
    connect(markerTypeCombox,SIGNAL(activated(int)), this, SLOT(setMarkerStyle(int)));


    /*marker size*/
    markerSizeCombox = new QComboBox(this);
    markerSizeCombox->addItem("0.5");
    markerSizeCombox->addItem("1");
    markerSizeCombox->addItem("2");
    markerSizeCombox->addItem("3");
    markerSizeCombox->addItem("4");
    markerSizeCombox->addItem("6");
    markerSizeCombox->addItem("8");
    markerSizeCombox->addItem("10");
    markerSizeCombox->setEditable(true);
    markerSizeCombox->lineEdit()->setText(QString::number(markerSize.rwidth()));
    connect(markerSizeCombox,SIGNAL(activated(int)), this, SLOT(setMarkerSize(int)));


    /*marker bush*/
    btnMarkerBrush = new QPushButton(this);
    btnMarkerBrush->setIcon(createColorToolButtonIcon(tr("images/floodfill.png"),markerBrush.color()));
    connect(btnMarkerBrush,SIGNAL(clicked()), this, SLOT(setMarkerBush()));

    /*marker pen*/
    btnMarkerPen = new QPushButton(this);
    btnMarkerPen->setIcon(createColorToolButtonIcon(tr("images/linecolor.png"),markerPen.color()));
    connect(btnMarkerPen,SIGNAL(clicked()), this, SLOT(setMarkerPen()));

    /*}}}*/


    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | \
        QDialogButtonBox::Cancel);
    connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(btnBox);

    QGridLayout *layout = new QGridLayout;
    /*name*/
    layout->addWidget(nameLabel,0,0);
    layout->addWidget(nameText,0,1);
    /*line*/
    layout->addWidget(lineLabel,1,0);
    layout->addWidget(lineTypeCombox,1,1);
    layout->addWidget(curveWidthCombox,1,2);
    layout->addWidget(btnLineColor,1,3);
    /*marker*/
    layout->addWidget(markerLabel,2,0);
    layout->addWidget(markerTypeCombox,2,1);
    layout->addWidget(markerSizeCombox,2,2);
    layout->addWidget(btnMarkerBrush,2,3);
    layout->addWidget(btnMarkerPen,2,4);
    layout->addLayout(btnLayout,3,0,1,5);

    /*alignment*/
    layout->itemAtPosition(0,0)->setAlignment(Qt::AlignRight);
    layout->itemAtPosition(1,0)->setAlignment(Qt::AlignRight);
    layout->itemAtPosition(2,0)->setAlignment(Qt::AlignRight);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);
}


IcvCurvePropertyDialog::~IcvCurvePropertyDialog()
{

}


QwtPlotCurve* IcvCurvePropertyDialog::getCurve()
{
    if(NULL == curve)
        return NULL;

    QwtPlotCurve *qwtcurve = curve->getCurve();
    return (qwtcurve != NULL)? qwtcurve : NULL;
}


const QwtSymbol* IcvCurvePropertyDialog::getSymbol()
{
    const QwtSymbol *symbol = NULL;

    if(NULL == curve)
        return NULL;

    return curve->getCurve()->symbol();
}


void IcvCurvePropertyDialog::accept()
{
    QString curveName = nameText->text();
    Qt::PenStyle styleTarget = Qt::SolidLine;
    bool ok = false;
    int widthTarget = 0;
    QColor colorTarget(Qt::black);


    if(NULL == curve || NULL ==getCurve())
        return QDialog::accept();

    /*Change the selected curve name*/
    if(0 != curveName.size())
        getCurve()->setTitle(curveName);

    /*Change the selected curve style*/
    ok          = false;
    widthTarget = curveWidthCombox->lineEdit()->text().toInt(&ok);
    colorTarget = curveColor;
    styleTarget = curveStyle;

    QPen pen = getCurve()->pen();
    pen.setColor(colorTarget);
    pen.setStyle(styleTarget);
    getCurve()->setPen(pen);


    /*Change marker attached to the selected curve */
    qint16 size = 0;
    ok          = false;
    size        = markerSizeCombox->currentText().toInt(&ok);
    markerSize  = QSize(size,size);

    QList<QwtPlotMarker *> markers = curve->getMarkers();
    for(qint16 pos= 0; pos < markers.count(); pos++)
    {    
        markers[pos]->setSymbol(new QwtSymbol(markerStyle, markerBrush, markerPen, markerSize));
    }

    if(NULL == curve->getCanvas())
        return ;

    if(NULL == curve->getCanvas()->getCanvas())
        return ;

    /*update curve*/
    QwtPlot *plot = curve->getCanvas()->getCanvas()->plot();
    plot->replot();

    return QDialog::accept ();
}


void IcvCurvePropertyDialog::reject()
{
    return QDialog::reject ();
}


QIcon IcvCurvePropertyDialog::createColorToolButtonIcon(const QString imageFile, QColor color)
{
    QPixmap pixmap(50,80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QPixmap image(imageFile);
    QRect target(0,0,50,60);
    QRect source(0,0,42,42);

    painter.fillRect(QRect(0,60,50,80),color);
    painter.drawPixmap(target,image, source);

    return QIcon(pixmap);
}


void IcvCurvePropertyDialog::setCurveStyle(int indexSel)
{
    bool ok = false;
    int style = indexSel+1;
    curveStyle = static_cast<Qt::PenStyle>(style);

    return ;
}


void IcvCurvePropertyDialog::setCurveWidth(int indexSel)
{
    bool ok = false;
    QString str = curveWidthCombox->itemText(indexSel);
    curveWidth = str.toInt(&ok);

    return ;
}


void IcvCurvePropertyDialog::setCurveColor()
{
    QColor colorUsing;
    if(NULL == getCurve())
        return;
    colorUsing = getCurve()->pen().color();
    QColor color = QColorDialog::getColor(colorUsing,this,tr("Select color"));
    curveColor = color;
    btnLineColor->setIcon(createColorToolButtonIcon(tr("images/linecolor.png"),color));
    
    return ;
}


void IcvCurvePropertyDialog::setMarkerStyle(int indexSel)
{
    markerStyle =  static_cast<QwtSymbol::Style>(indexSel-1);

    return;
}

void IcvCurvePropertyDialog::setMarkerBush()
{
    QColor colorUsing = markerBrush.color();
    QColor color = QColorDialog::getColor(colorUsing,this,tr("Select color"));
    markerBrush = QBrush(color);
    btnMarkerBrush->setIcon(createColorToolButtonIcon(tr("images/floodfill.png"),color));

    return ;
}


void IcvCurvePropertyDialog::setMarkerPen()
{
    QColor colorUsing = markerPen.color();
    QColor color = QColorDialog::getColor(colorUsing,this,tr("Select color"));
    markerPen = QPen(color);
    btnMarkerPen->setIcon(createColorToolButtonIcon(tr("images/linecolor.png"),color));

    return ;
}


void IcvCurvePropertyDialog::setMarkerSize(int indexSel)
{
    markerSizeCombox->setCurrentIndex(indexSel);

    return ;
}


bool IcvCurvePropertyDialog::eventFilter ( QObject * obj, QEvent * event )
{
    if(QEvent::MouseMove == event->type())
        return true;
    else
        return QDialog::eventFilter ( obj, event );
}


