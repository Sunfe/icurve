#include "icurve.h"

icurve::icurve(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	
	setWindowTitle("iCurve");
	setWindowIcon(QIcon(":/images/iCurve.ico"));
    setContentsMargins(5,5,50,5);
	
	QPalette mainWinPalette;
	mainWinPalette.setColor(QPalette::Background,Qt::lightGray);
	setPalette(mainWinPalette);

	plot = new QwtPlot();
	plot->setTitle( "unamed" );
	

	plot->setAxisTitle(QwtPlot::xBottom, "X");
	plot->setAxisTitle(QwtPlot::yLeft, "Y");
	
	plot->setCanvasBackground( Qt::white );
	plot->setAxisScale( QwtPlot::yLeft, -150.0, 150.0 );
	plot->setAxisScale( QwtPlot::xBottom, 0, 5000 );
	
	plot->setAxisLabelAlignment(QwtPlot::xBottom,Qt::AlignLeft);
	plot->setAxisLabelAlignment(QwtPlot::yLeft,Qt::AlignTop);
	
    plot->plotLayout()->setAlignCanvasToScales( false );
	plot->plotLayout()->setCanvasMargin(0);

    QwtPlotLegendItem *le= new QwtPlotLegendItem();
	le->attach(plot);

	grid = new QwtPlotGrid();
	grid->attach( plot );

	( void ) new QwtPlotPanner( plot->canvas());
	( void ) new QwtPlotMagnifier(plot->canvas());

	setCentralWidget(plot);

}

icurve::~icurve()
{

}
