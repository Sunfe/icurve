#if 0
#ifndef ICV_MENUS_H
#define ICV_MENUS_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QRectF>
#include <QProgressDialog>
#include <QFileInfo>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_engine.h>
#include <qwt_color_map.h>
#include <qwt_text.h>
#include <qwt_text_engine.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_legenditem.h>
#include <qwt_plot_grid.h>
#include "ui_icurve.h"
#include "icurve_common.h"
#include "icv_command.h"
#include "icv_plot_canvas.h"


class IcvMenu : public QWidget
{
    Q_OBJECT

public:
    IcvMenu(QWidget *parent = 0, Qt::WFlags flags = 0);
  
    ~IcvMenu();
    void createCurvePopMenu(QWidget * parent);
    void createCurvePopMenuAction(QWidget * parent);

protected:
 

private:

private slots:


signals:


};

#endif // ICV_MENUS_H
#endif