/****************************************************************************
** Meta object code from reading C++ file 'icv_icurve.h'
**
** Created: Fri Jun 24 22:30:36 2016
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
      44,   14, // methods
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
     160,   10,   10,   10, 0x08,
     172,   10,   10,   10, 0x08,
     185,   10,   10,   10, 0x08,
     200,   10,   10,   10, 0x08,
     213,   10,   10,   10, 0x08,
     226,   10,   10,   10, 0x08,
     240,   10,   10,   10, 0x08,
     252,   10,   10,   10, 0x08,
     267,   10,   10,   10, 0x08,
     285,   10,   10,   10, 0x08,
     306,   10,   10,   10, 0x08,
     322,   10,   10,   10, 0x08,
     338,   10,   10,   10, 0x08,
     354,   10,   10,   10, 0x08,
     371,   10,   10,   10, 0x08,
     385,   10,   10,   10, 0x08,
     412,  399,   10,   10, 0x08,
     447,   10,   10,   10, 0x08,
     469,   10,   10,   10, 0x08,
     485,   10,   10,   10, 0x08,
     506,   10,   10,   10, 0x08,
     521,   10,   10,   10, 0x08,
     536,   10,   10,   10, 0x08,
     555,   10,   10,   10, 0x08,
     573,   10,   10,   10, 0x08,
     593,   10,   10,   10, 0x08,
     607,   10,   10,   10, 0x08,
     622,   10,   10,   10, 0x08,
     637,   10,   10,   10, 0x08,
     652,   10,   10,   10, 0x08,
     670,   10,   10,   10, 0x08,
     685,   10,   10,   10, 0x08,
     711,  703,   10,   10, 0x08,
     735,  730,   10,   10, 0x08,
     752,  703,   10,   10, 0x08,
     785,  773,   10,   10, 0x08,
     814,   11,   10,   10, 0x08,
     845,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvICurve[] = {
    "IcvICurve\0\0progress\0analyDataProgress(qint32)\0"
    "name,position,lineInfo\0"
    "displayCurveInfoSignal(QString,QString,QString)\0"
    "openFile()\0saveAs()\0closePlot()\0"
    "cutCurve()\0copyCurve()\0pasteCurve()\0"
    "removeCurves()\0hideCurves()\0showCurves()\0"
    "deleteCurve()\0findCurve()\0showAllCurve()\0"
    "selectAllCurves()\0selectInvertCurves()\0"
    "setCurveColor()\0setCurveWidth()\0"
    "setCurveStyle()\0setCurveMarker()\0"
    "expandCurve()\0filterCurve()\0type,keyword\0"
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
        case 5: cutCurve(); break;
        case 6: copyCurve(); break;
        case 7: pasteCurve(); break;
        case 8: removeCurves(); break;
        case 9: hideCurves(); break;
        case 10: showCurves(); break;
        case 11: deleteCurve(); break;
        case 12: findCurve(); break;
        case 13: showAllCurve(); break;
        case 14: selectAllCurves(); break;
        case 15: selectInvertCurves(); break;
        case 16: setCurveColor(); break;
        case 17: setCurveWidth(); break;
        case 18: setCurveStyle(); break;
        case 19: setCurveMarker(); break;
        case 20: expandCurve(); break;
        case 21: filterCurve(); break;
        case 22: filterCurvePreview((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 23: recoverCurveVisible(); break;
        case 24: showCurveInfo(); break;
        case 25: setCurveProperties(); break;
        case 26: setAxseScale(); break;
        case 27: setAxseTitle(); break;
        case 28: setAxseAlignment(); break;
        case 29: setAxseRotation(); break;
        case 30: setAxseProperties(); break;
        case 31: insertTitle(); break;
        case 32: insertXLabel(); break;
        case 33: insertYLabel(); break;
        case 34: insertLegend(); break;
        case 35: insertCurveName(); break;
        case 36: insertFooter(); break;
        case 37: insertIndicator(); break;
        case 38: enableZoomer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: zoomPlot((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 40: enableHandMove((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: legendChecked((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 42: updateAnalyProgressBar((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 43: cancelAnalyProgressBar(); break;
        default: ;
        }
        _id -= 44;
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
