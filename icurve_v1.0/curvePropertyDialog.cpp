
#include "curvePropertyDialog.h"
#include "curvePainter.h"
#include "iCurve.h"

    CurvePropertyDialog::CurvePropertyDialog(QWidget * parent,Qt::WindowFlags flag)
: QDialog(parent,flag)
{

    int currentIndex = 0;
    QwtText curveTitile;

    /*initialize private data member*/
    if( NULL != getCurve() )
    {
        curveStyle = getCurve()->pen().style();
        curveWidth = getCurve()->pen().width();
        curveColor = getCurve()->pen().color();
        curveTitile = getCurve()->title();
    }
    else
    {
        curveStyle = Qt::SolidLine;
        curveWidth = 1;
        curveColor = Qt::black;
        curveTitile = QwtText(tr("unnamed"));
    }

    if( QwtSymbol::NoSymbol != getSymbol()->style())
    {
        markerStyle = getCurve()->symbol()->style();
        markerBrush = getCurve()->symbol()->brush();
        markerPen = getCurve()->symbol()->pen();
        markerSize = getCurve()->symbol()->size();
    }
    else
    {
        markerStyle = QwtSymbol::NoSymbol;
        markerBrush = QBrush(Qt::black);
        markerPen = QPen(Qt::black);
        markerSize = QSize(1,1);
    }

    /*initialize Object*/
    /*{{{curve*/
    setModal(false);
    nameLabel = new QLabel("Display Name:");
    nameText = new QLineEdit(this);
    nameText->setText(curveTitile.text());
    nameText->setFocus();
    nameLabel->setBuddy(nameText);

    lineLabel = new QLabel("Line:");
    lineTypeCombox = new QComboBox(this);
    lineTypeCombox->addItem("Solid");
    lineTypeCombox->addItem("Dot");
    lineTypeCombox->addItem("DashDot");
    lineTypeCombox->addItem("DashDotDot");
    connect(lineTypeCombox,SIGNAL(activated(int)), this, SLOT(setCurveStyle(int)));
    currentIndex = static_cast<int>(curveStyle - 1);
    lineTypeCombox->setCurrentIndex((currentIndex));

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

iCurve* CurvePropertyDialog:: figure()
{
    return qobject_cast < iCurve* >(parent());

}


const iCurve* CurvePropertyDialog:: figure() const
{
    return qobject_cast < const iCurve * >(parent());

}

QwtPlotCurve* CurvePropertyDialog::getCurve()
{
    QwtPlotCurve *curve = NULL;
    if( NULL == figure() )
        return NULL;

    curve = figure()->getPicker()->getCurve();
    if(NULL == curve)
        return NULL;

    return curve;
}

const QwtSymbol* CurvePropertyDialog::getSymbol()
{
    QwtPlotCurve *curve = NULL;
    const QwtSymbol * symbol = NULL;
    if( NULL == figure() )
        return NULL;

    /*if there is no curve selected, marker should not exist*/
    curve = figure()->getPicker()->getCurve();
    if(NULL == curve)
        return NULL;

    symbol = getCurve()->symbol();
    if(NULL == symbol)
        return NULL;

    return symbol;
}


void CurvePropertyDialog::accept()
{
    QString curveName = nameText->text();
    Qt::PenStyle styleTarget = Qt::SolidLine;
    bool ok = false;
    int widthTarget = 0;
    QColor colorTarget(Qt::black);
    int size = 0;

    if(NULL == getCurve())
        return QDialog::accept();

    /*Change the selected curve name*/
    if(0 != curveName.size())
        getCurve()->setTitle(curveName);

    /*Change the selected curve style*/
    ok = false;
    widthTarget =curveWidthCombox->lineEdit()->text().toInt(&ok);
    colorTarget = curveColor;
    styleTarget = curveStyle;

    QPen pen = getCurve()->pen();
    pen.setWidth( widthTarget );
    pen.setColor( colorTarget );
    pen.setStyle( styleTarget );
    getCurve()->setPen(pen);


    /*Change marker attached to the selected curve */
    ok = false;
    size = markerSizeCombox->currentText().toInt(&ok);
    markerSize = QSize(size,size);
    const QwtSymbol *symbol = new QwtSymbol(markerStyle, markerBrush, markerPen, \
            markerSize);
    getCurve()->setSymbol(symbol);

    /*update curve*/
    QwtPlot *plot = figure()->getPlot();
    plot->replot();

    return QDialog::accept ();
}

void CurvePropertyDialog::reject()
{
    return QDialog::reject ();
}

QIcon CurvePropertyDialog::createColorToolButtonIcon(const QString imageFile, QColor color)
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

void CurvePropertyDialog::setCurveStyle(int indexSel)
{
    bool ok = false;
    int style = indexSel+1;
    curveStyle = static_cast<Qt::PenStyle>(style);

}

void CurvePropertyDialog::setCurveWidth(int indexSel)
{
    bool ok = false;
    QString str = curveWidthCombox->itemText(indexSel);
    curveWidth = str.toInt(&ok);
}


void CurvePropertyDialog::setCurveColor()
{
    QColor colorUsing;
    if(NULL == getCurve())
        return;
    colorUsing = getCurve()->pen().color();
    QColor color = QColorDialog::getColor(colorUsing,this,tr("Select color"));
    curveColor = color;
    btnLineColor->setIcon(createColorToolButtonIcon(tr("images/linecolor.png"),color));
}

void CurvePropertyDialog::setMarkerStyle(int indexSel)
{
    markerStyle =  static_cast<QwtSymbol::Style>(indexSel-1);
}

void CurvePropertyDialog::setMarkerBush()
{
    QColor colorUsing = markerBrush.color();
    QColor color = QColorDialog::getColor(colorUsing,this,tr("Select color"));
    markerBrush = QBrush(color);
    btnMarkerBrush->setIcon(createColorToolButtonIcon(tr("images/floodfill.png"),color));
}

void CurvePropertyDialog::setMarkerPen()
{
    QColor colorUsing = markerPen.color();
    QColor color = QColorDialog::getColor(colorUsing,this,tr("Select color"));
    markerPen = QPen(color);
    btnMarkerPen->setIcon(createColorToolButtonIcon(tr("images/linecolor.png"),color));
}

void CurvePropertyDialog::setMarkerSize(int indexSel)
{
    markerSizeCombox->setCurrentIndex(indexSel);
}

bool CurvePropertyDialog::eventFilter ( QObject * obj, QEvent * event )
{
    if(QEvent::MouseMove == event->type())
        return true;
    else
        return QDialog::eventFilter ( obj, event );
}


CurvePropertyDialog::~CurvePropertyDialog()
{

}
