/****************************************************************************
** Meta object code from reading C++ file 'icv_plot_canvas.h'
**
** Created: Sat May 28 13:56:34 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/icv_plot_canvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icv_plot_canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IcvPlotCanvas[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x08,
      63,   50,   14,   14, 0x08,
     101,   50,   14,   14, 0x08,
     139,   50,   14,   14, 0x08,
     178,   50,   14,   14, 0x08,
     221,   15,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvPlotCanvas[] = {
    "IcvPlotCanvas\0\0curve\0setCurveColor(IcvPlotCurve*)\0"
    "curve,action\0seCurvetWidth(IcvPlotCurve*,QAction*)\0"
    "setCurveStyle(IcvPlotCurve*,QAction*)\0"
    "setCurveMarker(IcvPlotCurve*,QAction*)\0"
    "setCurveMarkerSize(IcvPlotCurve*,QAction*)\0"
    "setCurveProperty(IcvPlotCurve*)\0"
};

const QMetaObject IcvPlotCanvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IcvPlotCanvas,
      qt_meta_data_IcvPlotCanvas, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IcvPlotCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IcvPlotCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IcvPlotCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IcvPlotCanvas))
        return static_cast<void*>(const_cast< IcvPlotCanvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int IcvPlotCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setCurveColor((*reinterpret_cast< IcvPlotCurve*(*)>(_a[1]))); break;
        case 1: seCurvetWidth((*reinterpret_cast< IcvPlotCurve*(*)>(_a[1])),(*reinterpret_cast< QAction*(*)>(_a[2]))); break;
        case 2: setCurveStyle((*reinterpret_cast< IcvPlotCurve*(*)>(_a[1])),(*reinterpret_cast< QAction*(*)>(_a[2]))); break;
        case 3: setCurveMarker((*reinterpret_cast< IcvPlotCurve*(*)>(_a[1])),(*reinterpret_cast< QAction*(*)>(_a[2]))); break;
        case 4: setCurveMarkerSize((*reinterpret_cast< IcvPlotCurve*(*)>(_a[1])),(*reinterpret_cast< QAction*(*)>(_a[2]))); break;
        case 5: setCurveProperty((*reinterpret_cast< IcvPlotCurve*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
