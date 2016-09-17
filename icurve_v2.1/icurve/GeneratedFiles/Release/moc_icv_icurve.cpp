/****************************************************************************
** Meta object code from reading C++ file 'icv_icurve.h'
**
** Created: Sat Sep 17 21:24:45 2016
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
      48,   14, // methods
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
     145,   10,   10,   10, 0x08,
     154,   10,   10,   10, 0x08,
     166,   10,   10,   10, 0x08,
     180,   10,   10,   10, 0x08,
     191,   10,   10,   10, 0x08,
     203,   10,   10,   10, 0x08,
     216,   10,   10,   10, 0x08,
     231,   10,   10,   10, 0x08,
     244,   10,   10,   10, 0x08,
     257,   10,   10,   10, 0x08,
     271,   10,   10,   10, 0x08,
     283,   10,   10,   10, 0x08,
     298,   10,   10,   10, 0x08,
     316,   10,   10,   10, 0x08,
     337,   10,   10,   10, 0x08,
     353,   10,   10,   10, 0x08,
     369,   10,   10,   10, 0x08,
     385,   10,   10,   10, 0x08,
     402,   10,   10,   10, 0x08,
     416,   10,   10,   10, 0x08,
     443,  430,   10,   10, 0x08,
     478,   10,   10,   10, 0x08,
     500,   10,   10,   10, 0x08,
     516,   10,   10,   10, 0x08,
     537,   10,   10,   10, 0x08,
     552,   10,   10,   10, 0x08,
     567,   10,   10,   10, 0x08,
     586,   10,   10,   10, 0x08,
     604,   10,   10,   10, 0x08,
     624,   10,   10,   10, 0x08,
     638,   10,   10,   10, 0x08,
     653,   10,   10,   10, 0x08,
     668,   10,   10,   10, 0x08,
     683,   10,   10,   10, 0x08,
     701,   10,   10,   10, 0x08,
     716,   10,   10,   10, 0x08,
     742,  734,   10,   10, 0x08,
     766,  761,   10,   10, 0x08,
     783,  734,   10,   10, 0x08,
     804,   10,   10,   10, 0x08,
     830,  818,   10,   10, 0x08,
     859,   11,   10,   10, 0x08,
     890,   10,   10,   10, 0x08,
     915,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IcvICurve[] = {
    "IcvICurve\0\0progress\0analyDataProgress(qint32)\0"
    "name,position,lineInfo\0"
    "displayCurveInfoSignal(QString,QString,QString)\0"
    "openFile()\0openRecentFile()\0saveAs()\0"
    "closePlot()\0refreshPlot()\0cutCurve()\0"
    "copyCurve()\0pasteCurve()\0removeCurves()\0"
    "hideCurves()\0showCurves()\0deleteCurve()\0"
    "findCurve()\0showAllCurve()\0selectAllCurves()\0"
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
    "aboutIcurve()\0itemInfo,on\0"
    "legendChecked(QVariant,bool)\0"
    "updateAnalyProgressBar(qint32)\0"
    "cancelAnalyProgressBar()\0"
    "updateRecentFileActions()\0"
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
        case 3: openRecentFile(); break;
        case 4: saveAs(); break;
        case 5: closePlot(); break;
        case 6: refreshPlot(); break;
        case 7: cutCurve(); break;
        case 8: copyCurve(); break;
        case 9: pasteCurve(); break;
        case 10: removeCurves(); break;
        case 11: hideCurves(); break;
        case 12: showCurves(); break;
        case 13: deleteCurve(); break;
        case 14: findCurve(); break;
        case 15: showAllCurve(); break;
        case 16: selectAllCurves(); break;
        case 17: selectInvertCurves(); break;
        case 18: setCurveColor(); break;
        case 19: setCurveWidth(); break;
        case 20: setCurveStyle(); break;
        case 21: setCurveMarker(); break;
        case 22: expandCurve(); break;
        case 23: filterCurve(); break;
        case 24: filterCurvePreview((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 25: recoverCurveVisible(); break;
        case 26: showCurveInfo(); break;
        case 27: setCurveProperties(); break;
        case 28: setAxseScale(); break;
        case 29: setAxseTitle(); break;
        case 30: setAxseAlignment(); break;
        case 31: setAxseRotation(); break;
        case 32: setAxseProperties(); break;
        case 33: insertTitle(); break;
        case 34: insertXLabel(); break;
        case 35: insertYLabel(); break;
        case 36: insertLegend(); break;
        case 37: insertCurveName(); break;
        case 38: insertFooter(); break;
        case 39: insertIndicator(); break;
        case 40: enableZoomer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: zoomPlot((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 42: enableHandMove((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: aboutIcurve(); break;
        case 44: legendChecked((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 45: updateAnalyProgressBar((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 46: cancelAnalyProgressBar(); break;
        case 47: updateRecentFileActions(); break;
        default: ;
        }
        _id -= 48;
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
