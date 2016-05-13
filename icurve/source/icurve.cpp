
#include "icurve.h"

icurve::icurve(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
	
    initMainWinStyle(this);
    plot = new QwtPlot();
	initMainPlotter(plot);

    setCentralWidget(plot);
}

icurve::~icurve()
{

}


void icurve::initMainWinStyle(QMainWindow *self)
{
	self->setWindowTitle("iCurve");
	self->setWindowIcon(QIcon(":/images/iCurve.ico"));
	self->setContentsMargins(0,0,0,0);
		
	QPalette mainWinPalette;
	mainWinPalette.setColor(QPalette::Background,Qt::lightGray);
	self->setPalette(mainWinPalette);
}


void icurve::initMainPlotter(QwtPlot *plot)
{

   plot->setTitle( "unamed" );
    
   // plot->setAxisTitle(QwtPlot::xBottom, "X");
   // plot->setAxisTitle(QwtPlot::yLeft, "Y");
    
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, -200.0, 200.0 );
    plot->setAxisScale( QwtPlot::xBottom, 0, 5000 );
    
    plot->setAxisLabelAlignment(QwtPlot::xBottom,Qt::AlignLeft);
    plot->setAxisLabelAlignment(QwtPlot::yLeft,Qt::AlignTop);
    
    plot->plotLayout()->setAlignCanvasToScales( false );
    plot->plotLayout()->setCanvasMargin(0);

    QwtPlotLegendItem *le= new QwtPlotLegendItem();
    le->attach(plot);

    grid = new QwtPlotGrid();
	grid->setMajorPen(QPen(Qt::DashLine));
	grid->setMinorPen(QPen(Qt::DashLine));	
    grid->attach( plot );

    ( void ) new QwtPlotPanner( plot->canvas());
    ( void ) new QwtPlotMagnifier(plot->canvas());
    
	return ;
}

