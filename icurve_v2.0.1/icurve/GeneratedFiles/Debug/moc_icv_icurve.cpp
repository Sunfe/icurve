/****************************************************************************
** Meta object code from reading C++ file 'icv_icurve.h'
**
** Created: Sat Jun 25 00:56:54 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/icv_icurve.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'icv_icurve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IcvICurve[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   11,   10,   10, 0x05,
      69,   46,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     117,   10,   10,   10, 0x08,
     128,   10,   10,   10, 0x08,
     137,   10,   10,   10, 0x08,
     149,   10,   10,   10, 0x08,
     163,   10,   10,   10, 0x08,
     174,   10,   10,   10, 0x08,
     186,   10,   10,   10, 0x08,
     199,   10,   10,   10, 0x08,
     214,   10,   10,   10, 0x08,
     227,   10,   10,   10, 0x08,
     240,   10,   10,   10, 0x08,
     254,   10,   10,   10, 0x08,
     266,   10,   10,   10, 0x08,
     281,   10,   10,   10, 0x08,
     299,   10,   10,   10, 0x08,
     320,   10,   10,   10, 0x08,
     336,   10,   10,   10, 0x08,
     352,   10,   10,   10, 0x08,
     368,   10,   10,   10, 0x08,
     385,   10,   10,   10, 0x08,
     399,   10,   10,   10, 0x08,
     426,  413,   10,   10, 0x08,
     461,   10,   10,   10, 0x08,
     483,   10,   10,   10, 0x08,
     499,   10,   10,   10, 0x08,
     520,   10,   10,   10, 0x08,
     535,   10,   10,   10, 0x08,
     550,   10,   10,   10, 0x08,
     569,   10,   10,   10, 0x08,
     587,   10,   10,   10, 0x08,
     607,   10,   10,   10, 0x08,
     621,   10,   10,   10, 0x08,
     636,   10,   10,   10, 0x08,
     651,   10,   10,   10, 0x08,
     666,   10,   10,   10, 0x08,
     684,   10,   10,   10, 0x08,
     699,   10,   10,   10, 0x08,
     725,  717,   10,   10, 0x08,
     749,  744,   10,   10, 0x08,
     766,  717,   10,   10, 0x08,
     799,  787,   10,   10, 0x08,
     828,   11,   10,   10, 0x08,
     859,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvICurve[] = {
    "IcvICurve\0\0progress\0analyDataProgress(qint32)\0"
    "name,position,lineInfo\0"
    "displayCurveInfoSignal(QString,QString,QString)\0"
    "openFile()\0saveAs()\0closePlot()\0"
    "refreshPlot()\0cutCurve()\0copyCurve()\0"
    "pasteCurve()\0removeCurves()\0hideCurves()\0"
    "showCurves()\0deleteCurve()\0findCurve()\0"
    "showAllCurve()\0selectAllCurves()\0"
    "selectInvertCurves()\0setCurveColor()\0"
    "setCurveWidth()\0setCurveStyle()\0"
    "setCurveMarker()\0expandCurve()\0"
    "filterCurve()\0type,keyword\0"
    "filterCurvePreview(qint16,QString)\0"
    "recoverCurveVisible()\0showCurveInfo()\0"
    "setCurveProperties()\0setAxseScale()\0"
    "setAxseTitle()\0setAxseAlignment()\0"
    "setAxseRotation()\0setAxseProperties()\0"
    "insertTitle()\0insertXLabel()\0"
    "insertYLabel()\0insertLegend()\0"
    "insertCurveName()\0insertFooter()\0"
    "insertIndicator()\0checked\0enableZoomer(bool)\0"
    "rect\0zoomPlot(QRectF)\0enableHandMove(bool)\0"
    "itemInfo,on\0legendChecked(QVariant,bool)\0"
    "updateAnalyProgressBar(qint32)\0"
    "cancelAnalyProgressBar()\0"
};

const QMetaObject IcvICurve::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_IcvICurve,
      qt_meta_data_IcvICurve, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IcvICurve::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IcvICurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IcvICurve::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IcvICurve))
        return static_cast<void*>(const_cast< IcvICurve*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int IcvICurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: analyDataProgress((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: displayCurveInfoSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: openFile(); break;
        case 3: saveAs(); break;
        case 4: closePlot(); break;
        case 5: refreshPlot(); break;
        case 6: cutCurve(); break;
        case 7: copyCurve(); break;
        case 8: pasteCurve(); break;
        case 9: removeCurves(); break;
        case 10: hideCurves(); break;
        case 11: showCurves(); break;
        case 12: deleteCurve(); break;
        case 13: findCurve(); break;
        case 14: showAllCurve(); break;
        case 15: selectAllCurves(); break;
        case 16: selectInvertCurves(); break;
        case 17: setCurveColor(); break;
        case 18: setCurveWidth(); break;
        case 19: setCurveStyle(); break;
        case 20: setCurveMarker(); break;
        case 21: expandCurve(); break;
        case 22: filterCurve(); break;
        case 23: filterCurvePreview((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 24: recoverCurveVisible(); break;
        case 25: showCurveInfo(); break;
        case 26: setCurveProperties(); break;
        case 27: setAxseScale(); break;
        case 28: setAxseTitle(); break;
        case 29: setAxseAlignment(); break;
        case 30: setAxseRotation(); break;
        case 31: setAxseProperties(); break;
        case 32: insertTitle(); break;
        case 33: insertXLabel(); break;
        case 34: insertYLabel(); break;
        case 35: insertLegend(); break;
        case 36: insertCurveName(); break;
        case 37: insertFooter(); break;
        case 38: insertIndicator(); break;
        case 39: enableZoomer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: zoomPlot((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 41: enableHandMove((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: legendChecked((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 43: updateAnalyProgressBar((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 44: cancelAnalyProgressBar(); break;
        default: ;
        }
        _id -= 45;
    }
    return _id;
}

// SIGNAL 0
void IcvICurve::analyDataProgress(qint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IcvICurve::displayCurveInfoSignal(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
